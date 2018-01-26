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
	for _, pkg := range []string{"unicode", "unicode/utf8", "unicode/utf16"} {
		if err := g.TranspilePackage(pkg); err != nil {
			fmt.Fprintf(os.Stderr, err.Error())
		}
	}
}
