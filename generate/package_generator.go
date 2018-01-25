package generate

import (
	"fmt"
	"go/ast"
	"go/types"
	"os"
	"path/filepath"
	"strings"
)

type HeaderMetadata struct {
	Include string
}

type PackageGenerator struct {
	IncludeDir string
	SourceDir  string
	TypeInfo   *types.Info
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
