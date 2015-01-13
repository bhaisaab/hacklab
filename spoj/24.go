package main

import (
	"fmt"
	"math/big"
)

func main() {
	var t, num int64
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		fmt.Scanf("%d", &num)
		if num < 2 {
			fmt.Println(1)
		} else {
			fmt.Println(big.NewInt(1).MulRange(2, num))
		}
	}
}
