package main

import "fmt"

func main() {
	var t int
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		var base, index int
		fmt.Scanf("%d %d", &base, &index)
		if index == 0 {
			fmt.Println(1)
			continue
		}

		//right to left binary method
		result := 1
		base = base % 10
		for index > 0 {
			if index%2 != 0 {
				result = (result * base) % 10
			}
			base = (base * base) % 10
			index >>= 1
		}
		fmt.Println(result)
	}
}
