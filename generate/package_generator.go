package generate

import (
	"fmt"
	"go/ast"
	"go/types"
	"os"
	"path/filepath"
	"strings"
)

type PackageGenerator struct {
	IncludeDir string
	SourceDir  string
	TypeInfo   *types.Info
}

func (g *PackageGenerator) TranspileGoFile(f *ast.File, name, pkgDir, pkgPath string) ([]HeaderDeclaration, error) {
	cppFile := filepath.Join(g.SourceDir, pkgPath, strings.TrimSuffix(name, ".go")+".cpp")

	os.MkdirAll(filepath.Dir(cppFile), 0700)
	cpp, err := os.Create(cppFile)
	if err != nil {
		return nil, err
	}
	defer cpp.Close()

	fg := &FileGenerator{
		TypeInfo:    g.TypeInfo,
		PackageName: f.Name.Name,
	}

	includePath := filepath.Join(filepath.Dir(pkgPath), f.Name.Name)
	fmt.Fprint(cpp, "// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.\n")
	fmt.Fprint(cpp, "#include <"+filepath.Join("gostd", includePath)+".hpp>\n\n")
	fmt.Fprint(cpp, "#pragma clang diagnostic push\n")
	fmt.Fprint(cpp, "#pragma clang diagnostic ignored \"-Wparentheses-equality\"\n\n")

	namespace := "gostd::" + strings.Join(strings.Split(includePath, "/"), "::")

	fmt.Fprintf(cpp, "namespace %v {\n\n", namespace)

	var declarations []HeaderDeclaration

	for _, decl := range f.Decls {
		if hppDecls := fg.transpileHeaderDeclaration(decl); hppDecls != nil {
			declarations = append(declarations, hppDecls...)
		}
		if cppDecl := fg.transpileDeclaration(decl, true); cppDecl != "" {
			fmt.Fprint(cpp, cppDecl+"\n")
		}
	}

	fmt.Fprintf(cpp, "} // namespace %v\n", namespace)

	fmt.Fprint(cpp, "\n#pragma clang diagnostic pop\n")

	return declarations, nil
}
