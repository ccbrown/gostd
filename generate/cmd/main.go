package main

import (
	"fmt"
	"os"

	"github.com/ccbrown/gostd/generate"
)

func main() {
	g := generate.Generator{
		IncludeDir: "./include",
		SourceDir:  "./src",
	}
	for _, pkg := range []struct {
		Path         string
		IncludeTests bool
	}{
		{Path: "unicode"},
		{Path: "unicode/utf8", IncludeTests: true},
		{Path: "unicode/utf16"},
	} {
		if err := g.TranspilePackage(pkg.Path, pkg.IncludeTests); err != nil {
			fmt.Fprintf(os.Stderr, err.Error())
		}
	}
}
