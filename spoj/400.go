package main

import "fmt"

func main() {
	var num int
	var m string
	for {
		fmt.Scanf("%d", &num)
		if num == 0 {
			break
		}
		fmt.Scanf("%s", &m)
		l := len(m)

		for i := 0; i < num; i++ {
			odd := true
			for j := i; j < l; {
				fmt.Print(string(m[j]))
				if odd {
					j += (2*(num-i) - 1)
				} else {
					j += 2*i + 1
				}
				odd = !odd
			}
		}
		fmt.Println()
	}
}
