package main

import "fmt"

func main() {
	var side int
	for {
		fmt.Scanf("%d", &side)
		if side == 0 {
			break
		}
		if side == 1 {
			fmt.Println(1)
		}
		result := 0
		counter := 1
		n := side
		// sides = 1*nC1 + 3*n-1C1 + 5*n-2C1...
		for ; n > 0; n-- {
			result += n * counter
			counter += 2
		}
		fmt.Println(result)
	}

}
