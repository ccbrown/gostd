package generate

import (
	"fmt"
	"go/ast"
	"go/build"
	"go/importer"
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

func (g *Generator) TranspilePackage(path string) error {
	pkg, err := build.Import(path, ".", 0)
	if err != nil {
		return err
	}

	if err := os.RemoveAll(filepath.Join(g.IncludeDir, "gostd", path)); err != nil {
		return err
	}
	if err := os.RemoveAll(filepath.Join(g.SourceDir, path)); err != nil {
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
		if strings.HasSuffix(fpath, "_test.go") {
			continue
		}
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
