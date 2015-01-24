package main

import (
	"fmt"
	"math/big"
)

func main() {
	for i := 0; i < 10; i++ {
		a := big.NewInt(0)
		b := big.NewInt(0)
		var expr string
		fmt.Scanf("%s", &expr)
		a.SetString(expr, 10)
		fmt.Scanf("%s", &expr)
		b.SetString(expr, 10)

		kl := big.NewInt(0)
		kl.Add(a, b)
		kl.Div(kl, big.NewInt(2))
		fmt.Println(kl)

		natalia := big.NewInt(0)
		natalia.Sub(a, b)
		natalia.Div(natalia, big.NewInt(2))
		fmt.Println(natalia)
	}
}
