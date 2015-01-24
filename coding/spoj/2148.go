package main

import "fmt"

func main() {

	var t int
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		var n, candy, candies int64
		fmt.Scanf("\n\n%d", &n)
		candies = 0
		for i := int64(0); i < n; i++ {
			fmt.Scanf("%d", &candy)
			candies = (candies + candy) % n
		}
		if candies%n == 0 {
			fmt.Println("YES")
		} else {
			fmt.Println("NO")
		}
	}

}
