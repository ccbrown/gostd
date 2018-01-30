package generate

import (
	"fmt"
	"go/ast"
	"go/build"
	"go/parser"
	"go/token"
	"go/types"
	"os"
	"path/filepath"
	"strings"
)

type Generator struct {
	IncludeDir string
	SourceDir  string
}

func (g *Generator) TranspilePackage(path string, includeTests bool) error {
	buildContext := build.Default
	pkg, err := buildContext.Import(path, ".", 0)
	if err != nil {
		return err
	}

	if err := os.RemoveAll(filepath.Join(g.IncludeDir, "gostd", path)); err != nil {
		return err
	}
	if err := os.RemoveAll(filepath.Join(g.SourceDir, path)); err != nil {
		return err
	}

	goFiles := append([]string(nil), pkg.GoFiles...)
	if includeTests {
		goFiles = append(goFiles, pkg.TestGoFiles...)
	}
	declarations, err := g.transpileFiles(&buildContext, pkg, goFiles, includeTests)
	if err != nil {
		return err
	}

	if err := g.writeHPPFile(path, declarations, pkg.Imports); err != nil {
		return err
	}

	if includeTests {
		if len(pkg.XTestGoFiles) > 0 {
			declarations, err := g.transpileFiles(&buildContext, pkg, pkg.XTestGoFiles, true)
			if err != nil {
				return err
			}

			if err := g.writeHPPFile(path+"_test", declarations, pkg.XTestImports); err != nil {
				return err
			}
		}
	}

	return nil
}

func (g *Generator) transpileFiles(buildContext *build.Context, pkg *build.Package, fileNames []string, includesTestFiles bool) ([]HeaderDeclaration, error) {
	pg := &PackageGenerator{
		IncludeDir: g.IncludeDir,
		SourceDir:  g.SourceDir,
		TypeInfo: &types.Info{
			Types:      make(map[ast.Expr]types.TypeAndValue),
			Defs:       make(map[*ast.Ident]types.Object),
			Uses:       make(map[*ast.Ident]types.Object),
			Selections: make(map[*ast.SelectorExpr]*types.Selection),
			Scopes:     make(map[ast.Node]*types.Scope),
		},
	}

	fset := token.NewFileSet()
	asts, err := parser.ParseDir(fset, pkg.Dir, nil, 0)
	if err != nil {
		return nil, err
	}

	var files []*ast.File
	var filePaths []string
	pkgName := pkg.Name
	for _, pkgAst := range asts {
		for fpath, file := range pkgAst.Files {
			match := false
			for _, fname := range fileNames {
				if fpath == filepath.Join(pkg.Dir, fname) {
					match = true
					break
				}
			}
			if match {
				pkgName = file.Name.Name
				files = append(files, file)
				filePaths = append(filePaths, fpath)
			}
		}
		if files != nil {
			break
		}
	}

	conf := &types.Config{
		Importer: NewImporter(buildContext, includesTestFiles),
	}
	if _, err := conf.Check(pkgName, fset, files, pg.TypeInfo); err != nil {
		return nil, err
	}

	var declarations []HeaderDeclaration
	for i, f := range files {
		hdrDecls, err := pg.TranspileGoFile(f, filepath.Base(filePaths[i]), pkg.Dir, pkg.ImportPath)
		if err != nil {
			return nil, err
		}
		declarations = append(declarations, hdrDecls...)
	}

	return declarations, nil
}

func (g *Generator) writeHPPFile(pkgPath string, declarations []HeaderDeclaration, imports []string) error {
	hppFile := filepath.Join(g.IncludeDir, "gostd", pkgPath+".hpp")
	os.MkdirAll(filepath.Dir(hppFile), 0700)
	hpp, err := os.Create(hppFile)
	if err != nil {
		return err
	}
	defer hpp.Close()

	fmt.Fprintf(hpp, "// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.\n")
	namespace := "gostd::" + strings.Join(strings.Split(pkgPath, "/"), "::")
	fmt.Fprint(hpp, "#pragma once\n\n#include <gostd.hpp>\n")
	for _, pkg := range imports {
		fmt.Fprint(hpp, "#include <gostd/"+pkg+".hpp>\n")
	}
	fmt.Fprintf(hpp, "\nnamespace %v {\n\n", namespace)
	for _, declaration := range SortHeaderDeclarations(declarations) {
		fmt.Fprintf(hpp, "%v\n", declaration.Declaration())
	}
	fmt.Fprint(hpp, "}\n")
	return nil
}
