package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"

	"go/ast"
	"go/build"
	"go/constant"
	"go/importer"
	"go/parser"
	"go/token"
	"go/types"
)

type Generator struct {
	IncludeDir string
	SourceDir  string
}

type PackageGenerator struct {
	IncludeDir string
	SourceDir  string
	TypeInfo   *types.Info
}

type FileGenerator struct {
	TypeInfo         *types.Info
	PackageName      string
	fallthroughLabel string
}

func (g *FileGenerator) namespaceForPackage(pkg string) string {
	if pkg == g.PackageName {
		return ""
	}
	panic(fmt.Errorf("unknown namespace for %v", pkg))
}

func (g *FileGenerator) transpileTypeExpression(expr ast.Expr) string {
	return g.transpileType(g.TypeInfo.Types[expr].Type)
}

func (g *FileGenerator) transpileType(t types.Type) string {
	switch t := t.(type) {
	case *types.Basic:
		switch t.Kind() {
		case types.Bool, types.Int, types.Int8, types.Int16, types.Int32, types.Int64, types.Uint,
			types.Uint8, types.Uint16, types.Uint32, types.Uint64, types.Uintptr, types.Float32,
			types.Float64, types.Complex64, types.Complex128, types.String:
			return "::gostd::" + strings.Title(t.String())
		}
	case *types.Array:
		return fmt.Sprintf("::gostd::Array<%v, %v>", g.transpileType(t.Elem()), t.Len())
	case *types.Named:
		obj := t.Obj()
		if namespace := g.namespaceForPackage(obj.Pkg().Path()); namespace != "" {
			return namespace + "::" + obj.Name()
		}
		return obj.Name()
	case *types.Slice:
		return "::gostd::Slice<" + g.transpileType(t.Elem()) + ">"
	}
	panic(fmt.Errorf("unsupported type type %T\n", t))
}

func (g *FileGenerator) transpileExpression(expr ast.Expr) string {
	switch expr := expr.(type) {
	case *ast.BasicLit:
		v := constant.MakeFromLiteral(expr.Value, expr.Kind, 0)
		switch expr.Kind {
		case token.CHAR:
			fallthrough
		case token.INT:
			ret := v.ExactString()
			if constant.BitLen(v) >= 31 {
				if constant.Sign(v) >= 0 {
					ret += "u"
				}
				ret += "ll"
			}
			return ret
		default:
			panic(fmt.Errorf("unsupported basic literal type %v\n", expr.Kind))
		}
	case *ast.BinaryExpr:
		op := expr.Op.String()
		if op == "&^" {
			op = "&~"
		}
		return "(" + g.transpileExpression(expr.X) + op + g.transpileExpression(expr.Y) + ")"
	case *ast.CompositeLit:
		t := g.TypeInfo.Types[expr.Type].Type
		if ar, ok := t.(*types.Array); ok {
			values := make([]ast.Expr, ar.Len())
			i := int64(0)
			for _, e := range expr.Elts {
				if kv, ok := e.(*ast.KeyValueExpr); ok {
					if v, ok := constant.Int64Val(g.TypeInfo.Types[kv.Key].Value); ok {
						i = v
					} else {
						panic("invalid key expression")
					}
					values[i] = kv.Value
				} else {
					values[i] = e
				}
				i++
			}
			ret := "{"
			for i, v := range values {
				if i > 0 {
					ret += ", "
				}
				ret += g.transpileType(ar.Elem()) + "(" + g.transpileExpression(v) + ")"
			}
			ret += "}"
			return ret
		} else {
			ret := "{"
			for i, v := range expr.Elts {
				if i > 0 {
					ret += ", "
				}
				ret += g.transpileExpression(v)
			}
			ret += "}"
			return ret
		}
	case *ast.Ident:
		if obj := g.TypeInfo.Uses[expr]; obj != nil {
			if obj.Pkg() == nil {
				switch obj.Name() {
				case "bool", "string", "int", "int8", "int16", "int32", "int64", "uint", "uint8",
					"uint16", "uint32", "uint64", "uintptr", "byte", "rune", "float32", "float64",
					"complex64", "complex128", "len", "append":
					return "::gostd::" + strings.Title(obj.Name())
				}
			}
		}
		return expr.Name
	case *ast.CallExpr:
		return g.transpileExpression(expr.Fun) + "(" + strings.Join(g.transpileExpressions(expr.Args), ", ") + ")"
	case *ast.IndexExpr:
		return g.transpileExpression(expr.X) + "[" + g.transpileExpression(expr.Index) + "]"
	case *ast.ParenExpr:
		return "(" + g.transpileExpression(expr.X) + ")"
	case *ast.SliceExpr:
		exprs := g.transpileExpressions([]ast.Expr{expr.X, expr.Low, expr.High, expr.Max})
		ret := exprs[0]
		if expr.Max != nil {
			ret += fmt.Sprintf(".Head(%v)", exprs[2])
		}
		if expr.Low != nil {
			ret += fmt.Sprintf(".Tail(%v)", exprs[1])
		}
		if expr.Slice3 || expr.Max != nil {
			panic(fmt.Errorf("full slice expressions not yet supported"))
		}
		return ret
	case *ast.UnaryExpr:
		return expr.Op.String() + g.transpileExpression(expr.X)
	case *ast.SelectorExpr:
		return g.transpileExpression(expr.X) + "." + expr.Sel.Name
	}
	//panic(fmt.Errorf("unsupported expression type %T\n", expr))
	return fmt.Sprintf("/* %T */", expr)
}

func (g *FileGenerator) transpileExpressions(exprs []ast.Expr) []string {
	ret := []string{}
	for _, expr := range exprs {
		if expr == nil {
			ret = append(ret, "")
			continue
		}
		ret = append(ret, g.transpileExpression(expr))
	}
	return ret
}

func (g *FileGenerator) transpileStatement(stmt ast.Stmt) string {
	switch stmt := stmt.(type) {
	case *ast.AssignStmt:
		left := g.transpileExpressions(stmt.Lhs)
		right := g.transpileExpressions(stmt.Rhs)
		isDeclaration := stmt.Tok == token.DEFINE
		for i, l := range left {
			if l == "_" {
				left[i] = fmt.Sprintf("_%v", stmt.Lhs[i].Pos())
				isDeclaration = true
			}
		}
		ret := ""
		if len(stmt.Lhs) > 1 {
			ret += fmt.Sprintf("auto [%v]", strings.Join(left, ", "))
		} else if isDeclaration {
			if g.TypeInfo.Types[stmt.Rhs[0]].Value != nil {
				ret += fmt.Sprintf("::gostd::Int %v", left[0])
			} else {
				ret += fmt.Sprintf("auto %v", left[0])
			}
		} else {
			ret += left[0]
		}
		if stmt.Tok == token.DEFINE {
			ret += "="
		} else {
			ret += stmt.Tok.String()
		}
		ret += strings.Join(right, ", ")
		return ret
	case *ast.BranchStmt:
		switch stmt.Tok {
		case token.BREAK:
			return "break"
		case token.CONTINUE:
			return "continue"
		case token.FALLTHROUGH:
			return "goto " + g.fallthroughLabel
		}
	case *ast.ForStmt:
		ret := "for ("
		if stmt.Init != nil {
			ret += g.transpileStatement(stmt.Init)
		}
		ret += ";"
		if stmt.Cond != nil {
			ret += g.transpileExpression(stmt.Cond)
		}
		ret += ";"
		if stmt.Post != nil {
			ret += g.transpileStatement(stmt.Post)
		}
		ret += ")" + g.transpileStatement(stmt.Body)
		return ret
	case *ast.IfStmt:
		cond := g.transpileExpression(stmt.Cond)
		body := g.transpileStatement(stmt.Body)
		ret := ""
		if stmt.Init != nil {
			ret += fmt.Sprintf("if (%v; %v) %v", g.transpileStatement(stmt.Init), cond, body)
		} else {
			ret += fmt.Sprintf("if (%v) %v", cond, body)
		}
		if stmt.Else != nil {
			ret += " else " + g.transpileStatement(stmt.Else)
		}
		return ret
	case *ast.IncDecStmt:
		return g.transpileExpression(stmt.X) + stmt.Tok.String()
	case *ast.ReturnStmt:
		if stmt.Results != nil {
			exprs := g.transpileExpressions(stmt.Results)
			if len(exprs) > 1 {
				return "return {" + strings.Join(exprs, ", ") + "}"
			} else {
				return "return " + exprs[0]
			}
		}
	case *ast.BlockStmt:
		ret := "{\n"
		for _, stmt := range stmt.List {
			ret += g.transpileStatement(stmt) + ";\n"
		}
		ret += "}"
		return ret
	case *ast.DeclStmt:
		return g.transpileDeclaration(stmt.Decl, AllDeclarations)
	case *ast.SwitchStmt:
		ret := "{"
		if stmt.Init != nil {
			ret += "if (" + g.transpileStatement(stmt.Init) + "; "
		} else {
			ret += "if ("
		}
		for i, e := range stmt.Body.List {
			cc := e.(*ast.CaseClause)
			if cc.List == nil {
				continue
			}
			if i > 0 {
				ret += " else if ("
			}
			ret += "(" + strings.Join(g.transpileExpressions(cc.List), ") || (") + fmt.Sprintf(")) {\n_case%v:\n", e.Pos())
			prevFallthroughLabel := g.fallthroughLabel
			if i+1 < len(stmt.Body.List) {
				g.fallthroughLabel = fmt.Sprintf("_case%v", stmt.Body.List[i+1].Pos())
			}
			for _, stmt := range cc.Body {
				ret += g.transpileStatement(stmt) + ";\n"
			}
			g.fallthroughLabel = prevFallthroughLabel
			ret += "}\n"
		}
		for i, e := range stmt.Body.List {
			cc := e.(*ast.CaseClause)
			if cc.List == nil {
				ret += fmt.Sprintf(" else {\n_case%v:", e.Pos())
				prevFallthroughLabel := g.fallthroughLabel
				if i+1 < len(stmt.Body.List) {
					g.fallthroughLabel = fmt.Sprintf("_case%v", stmt.Body.List[i+1].Pos())
				}
				for _, stmt := range cc.Body {
					ret += g.transpileStatement(stmt) + ";\n"
				}
				g.fallthroughLabel = prevFallthroughLabel
				ret += "}\n"
				break
			}
		}
		ret += "}"
		return ret
	}
	//panic(fmt.Errorf("unsupported statement type %T\n", stmt))
	return fmt.Sprintf("/* %T */", stmt)
}

func (g *FileGenerator) transpileFunctionDeclaration(decl *ast.FuncDecl) string {
	ret := ""
	if len(decl.Type.Results.List) == 0 {
		ret += "void"
	} else if len(decl.Type.Results.List) == 1 && len(decl.Type.Results.List[0].Names) <= 1 {
		ret += g.transpileTypeExpression(decl.Type.Results.List[0].Type)
	} else {
		first := true
		ret += "::gostd::Tuple<"
		for _, field := range decl.Type.Results.List {
			if !first {
				ret += ", "
			}
			for _ = range field.Names {
				ret += g.transpileTypeExpression(field.Type)
			}
			first = false
		}
		ret += ">"
	}
	ret += fmt.Sprintf(" %v(", decl.Name.Name)
	first := true
	for _, field := range decl.Type.Params.List {
		if !first {
			ret += ", "
		}
		for _, name := range field.Names {
			ret += fmt.Sprintf("%v %v", g.transpileTypeExpression(field.Type), name)
		}
		first = false
	}
	ret += ")"
	return ret
}

type DeclarationClass int

const (
	HeaderDeclarations DeclarationClass = iota
	CPPDeclarations
	AllDeclarations
)

func (g *FileGenerator) transpileDeclaration(decl ast.Decl, class DeclarationClass) string {
	switch decl := decl.(type) {
	case *ast.GenDecl:
		switch decl.Tok {
		case token.CONST:
			if class == CPPDeclarations {
				return ""
			}
			ret := ""
			for _, spec := range decl.Specs {
				vspec := spec.(*ast.ValueSpec)
				ret += fmt.Sprintf("constexpr auto %v = ::gostd::UntypedConstant(%v);\n", vspec.Names[0], g.transpileExpression(vspec.Values[0]))
			}
			return ret
		case token.TYPE:
			if class == CPPDeclarations {
				return ""
			}
			ret := ""
			for _, spec := range decl.Specs {
				tspec := spec.(*ast.TypeSpec)
				switch t := tspec.Type.(type) {
				case *ast.StructType:
					ret += "struct " + tspec.Name.Name + " {\n"
					for _, field := range t.Fields.List {
						for _, name := range field.Names {
							ret += g.transpileTypeExpression(field.Type) + " " + name.Name + ";\n"
						}
					}
					ret += "};\n"
				}
			}
			return ret
		case token.VAR:
			ret := ""
			for _, spec := range decl.Specs {
				vspec := spec.(*ast.ValueSpec)
				for i, name := range vspec.Names {
					var t types.Type
					if vspec.Type != nil {
						t = g.TypeInfo.Types[vspec.Type].Type
					} else {
						t = g.TypeInfo.Types[vspec.Values[i]].Type
					}
					if class == HeaderDeclarations {
						ret += "extern " + g.transpileType(t) + " " + name.Name + ";\n"
					} else if vspec.Values != nil {
						ret += g.transpileType(t) + " " + name.Name + " = " + g.transpileExpression(vspec.Values[i]) + ";\n"
					} else {
						ret += g.transpileType(t) + " " + name.Name + ";\n"
					}
				}
			}
			return ret
		}
	case *ast.FuncDecl:
		ret := g.transpileFunctionDeclaration(decl)
		if class == HeaderDeclarations {
			return ret + ";\n"
		}
		ret += " "
		hasNamedReturnValues := false
		for _, field := range decl.Type.Results.List {
			for _, name := range field.Names {
				if !hasNamedReturnValues {
					ret += "{\n"
				}
				hasNamedReturnValues = true
				ret += g.transpileTypeExpression(field.Type) + " " + name.Name + ";\n"
			}
		}
		ret += g.transpileStatement(decl.Body)
		if hasNamedReturnValues {
			ret += "}\n"
		}
		ret += "\n"
		return ret
	}
	//panic(fmt.Errorf("unsupported declaration type %T\n", decl))
	return fmt.Sprintf("/* %T */\n\n", decl)
}

type HeaderMetadata struct {
	Include string
}

func (g *PackageGenerator) TranspileGoFile(f *ast.File, name, pkgDir, pkgPath string) (*HeaderMetadata, error) {
	include := filepath.Join("gostd", pkgPath, "_"+strings.TrimSuffix(name, ".go")+".hpp")
	cppFile := filepath.Join(g.SourceDir, pkgPath, strings.TrimSuffix(name, ".go")+".cpp")
	hppFile := filepath.Join(g.IncludeDir, include)

	os.MkdirAll(filepath.Dir(cppFile), 0700)
	cpp, err := os.Create(cppFile)
	if err != nil {
		return nil, err
	}
	defer cpp.Close()

	os.MkdirAll(filepath.Dir(hppFile), 0700)
	hpp, err := os.Create(hppFile)
	if err != nil {
		return nil, err
	}
	defer hpp.Close()

	fg := &FileGenerator{
		TypeInfo:    g.TypeInfo,
		PackageName: f.Name.Name,
	}

	fmt.Fprint(cpp, "// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.\n")
	fmt.Fprint(cpp, "#include <"+filepath.Join("gostd", pkgPath)+".hpp>\n\n")
	fmt.Fprint(cpp, "#pragma clang diagnostic push\n")
	fmt.Fprint(cpp, "#pragma clang diagnostic ignored \"-Wparentheses-equality\"\n\n")

	fmt.Fprint(hpp, "// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.\n")
	fmt.Fprint(hpp, "#pragma once\n\n")
	fmt.Fprint(hpp, "#include <gostd.hpp>\n\n")

	namespace := "gostd::" + strings.Join(strings.Split(pkgPath, "/"), "::")

	fmt.Fprintf(cpp, "namespace %v {\n\n", namespace)
	fmt.Fprintf(hpp, "namespace %v {\n\n", namespace)

	for _, decl := range f.Decls {
		if hppDecl := fg.transpileDeclaration(decl, HeaderDeclarations); hppDecl != "" {
			fmt.Fprint(hpp, hppDecl+"\n")
		}
		if cppDecl := fg.transpileDeclaration(decl, CPPDeclarations); cppDecl != "" {
			fmt.Fprint(cpp, cppDecl+"\n")
		}
	}

	fmt.Fprintf(cpp, "} // namespace %v\n", namespace)
	fmt.Fprintf(hpp, "} // namespace %v\n", namespace)

	fmt.Fprint(cpp, "\n#pragma clang diagnostic pop\n")

	return &HeaderMetadata{
		Include: include,
	}, nil
}

func (g *Generator) TranspilePackage(path string) error {
	pkg, err := build.Import(path, ".", 0)
	if err != nil {
		return err
	}

	pg := &PackageGenerator{
		IncludeDir: g.IncludeDir,
		SourceDir:  g.SourceDir,
		TypeInfo: &types.Info{
			Types:  make(map[ast.Expr]types.TypeAndValue),
			Defs:   make(map[*ast.Ident]types.Object),
			Uses:   make(map[*ast.Ident]types.Object),
			Scopes: make(map[ast.Node]*types.Scope),
		},
	}

	conf := &types.Config{
		Importer: importer.Default(),
	}
	fset := token.NewFileSet()
	var files []*ast.File
	pkgs, err := parser.ParseDir(fset, pkg.Dir, nil, 0)
	if err != nil {
		return err
	}
	for _, file := range pkgs[pkg.Name].Files {
		files = append(files, file)
	}
	if _, err := conf.Check(pkg.Name, fset, files, pg.TypeInfo); err != nil {
		return err
	}

	headers := []*HeaderMetadata{}
	for fpath, f := range pkgs[pkg.Name].Files {
		metadata, err := pg.TranspileGoFile(f, filepath.Base(fpath), pkg.Dir, path)
		if err != nil {
			return err
		}
		headers = append(headers, metadata)
	}

	hppFile := filepath.Join(g.IncludeDir, "gostd", path+".hpp")
	hpp, err := os.Create(hppFile)
	if err != nil {
		return err
	}
	defer hpp.Close()

	fmt.Fprintf(hpp, "// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.\n")
	fmt.Fprint(hpp, "#pragma once\n\n")
	for _, header := range headers {
		fmt.Fprintf(hpp, "#include <%v>\n", header.Include)
	}
	return nil
}

func main() {
	g := Generator{
		IncludeDir: "./include",
		SourceDir:  "./src",
	}
	if err := g.TranspilePackage("unicode/utf8"); err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
	}
}
