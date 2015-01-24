package main

import "fmt"

func main() {
	var a, b, c int
	for {
		fmt.Scanf("%d %d %d", &a, &b, &c)
		if a == 0 && b == 0 && c == 0 {
			break
		}
		if c == (b + (b - a)) {
			fmt.Println("AP", c+(c-b))
		} else {
			fmt.Println("GP", c/b*c)
		}
	}
}
