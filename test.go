package main

import (
	"debug/macho"
	"fmt"
	"os"
)

func main() {
	f, err := os.Open("./obj/cpp/cstdlib.o")
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer f.Close()
	mf, err := macho.NewFile(f)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer mf.Close()
	for _, sym := range mf.Symtab.Syms {
		fmt.Println(sym.Name)
	}
	fmt.Println("vim-go")
}
