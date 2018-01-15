package main

import "testing"

func TestFoo(t *testing.T) {
	for name, tc := range map[string]struct {
		I int
		F float64
	}{
		"OneTwo": {1, 2.0},
		"OneOne": {1, 1.0},
	} {
		t.Run(name, func(t *testing.T) {
			// do stuff
		})
	}
}
