package generate

import (
	"fmt"
	"go/ast"
	"go/build"
	"go/parser"
	"go/token"
	"go/types"
	"path/filepath"
	"sync"
)

// This is a modified version of go/internal/srcimporter.Importer.
//
// https://github.com/golang/go/blob/b26ad605a92af65deef30eb196ff2173566ee60f/src/go/internal/srcimporter/srcimporter.go
// https://github.com/golang/go/blob/b26ad605a92af65deef30eb196ff2173566ee60f/LICENSE
type Importer struct {
	ctxt             *build.Context
	fset             *token.FileSet
	sizes            types.Sizes
	packages         map[string]*types.Package
	includeTestFiles bool
}

func NewImporter(ctxt *build.Context, includeTestFiles bool) *Importer {
	return &Importer{
		ctxt:             ctxt,
		fset:             token.NewFileSet(),
		sizes:            types.SizesFor(ctxt.Compiler, ctxt.GOARCH),
		packages:         make(map[string]*types.Package),
		includeTestFiles: includeTestFiles,
	}
}

var importing types.Package

func (p *Importer) Import(path string) (*types.Package, error) {
	return p.ImportFrom(path, "", 0)
}

func (p *Importer) ImportFrom(path, srcDir string, mode types.ImportMode) (*types.Package, error) {
	if mode != 0 {
		panic("non-zero import mode")
	}

	var bp *build.Package
	var err error
	switch {
	default:
		if abs, err := p.absPath(srcDir); err == nil {
			srcDir = abs
		}
		bp, err = p.ctxt.Import(path, srcDir, build.FindOnly)

	case build.IsLocalImport(path):
		bp, err = p.ctxt.ImportDir(filepath.Join(srcDir, path), build.FindOnly)

	case p.isAbsPath(path):
		return nil, fmt.Errorf("invalid absolute import path %q", path)
	}
	if err != nil {
		return nil, err
	}

	if bp.ImportPath == "unsafe" {
		return types.Unsafe, nil
	}

	pkg := p.packages[bp.ImportPath]
	if pkg != nil {
		if pkg == &importing {
			return nil, fmt.Errorf("import cycle through package %q", bp.ImportPath)
		}
		if !pkg.Complete() {
			return pkg, fmt.Errorf("reimported partially imported package %q", bp.ImportPath)
		}
		return pkg, nil
	}

	p.packages[bp.ImportPath] = &importing
	defer func() {
		if p.packages[bp.ImportPath] == &importing {
			p.packages[bp.ImportPath] = nil
		}
	}()

	bp, err = p.ctxt.ImportDir(bp.Dir, 0)
	if err != nil {
		return nil, err
	}
	var filenames []string
	filenames = append(filenames, bp.GoFiles...)
	filenames = append(filenames, bp.CgoFiles...)
	if p.includeTestFiles {
		filenames = append(filenames, bp.TestGoFiles...)
		p.includeTestFiles = false
		defer func() {
			p.includeTestFiles = true
		}()
	}

	files, err := p.parseFiles(bp.Dir, filenames)
	if err != nil {
		return nil, err
	}

	conf := types.Config{
		IgnoreFuncBodies: true,
		FakeImportC:      true,
		Importer:         p,
		Sizes:            p.sizes,
	}
	pkg, err = conf.Check(bp.ImportPath, p.fset, files, nil)
	if err != nil {
		return nil, fmt.Errorf("type-checking package %q failed (%v)", bp.ImportPath, err)
	}

	p.packages[bp.ImportPath] = pkg
	return pkg, nil
}

func (p *Importer) parseFiles(dir string, filenames []string) ([]*ast.File, error) {
	open := p.ctxt.OpenFile

	files := make([]*ast.File, len(filenames))
	errors := make([]error, len(filenames))

	var wg sync.WaitGroup
	wg.Add(len(filenames))
	for i, filename := range filenames {
		go func(i int, filepath string) {
			defer wg.Done()
			if open != nil {
				src, err := open(filepath)
				if err != nil {
					errors[i] = fmt.Errorf("opening package file %s failed (%v)", filepath, err)
					return
				}
				files[i], errors[i] = parser.ParseFile(p.fset, filepath, src, 0)
				src.Close()
			} else {
				files[i], errors[i] = parser.ParseFile(p.fset, filepath, nil, 0)
			}
		}(i, p.joinPath(dir, filename))
	}
	wg.Wait()

	for _, err := range errors {
		if err != nil {
			return nil, err
		}
	}

	return files, nil
}

func (p *Importer) absPath(path string) (string, error) {
	return filepath.Abs(path)
}

func (p *Importer) isAbsPath(path string) bool {
	if f := p.ctxt.IsAbsPath; f != nil {
		return f(path)
	}
	return filepath.IsAbs(path)
}

func (p *Importer) joinPath(elem ...string) string {
	if f := p.ctxt.JoinPath; f != nil {
		return f(elem...)
	}
	return filepath.Join(elem...)
}
