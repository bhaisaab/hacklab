package main

import "fmt"

func main() {

	primes := make([]int, 0)
	for i := 2; i < 32000; i++ {
		isPrime := true
		for _, num := range primes {
			if i%num == 0 {
				isPrime = false
				break
			}
		}
		if isPrime {
			primes = append(primes, i)
		}
	}

	var t int
	var a, b int
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		fmt.Scanf("%d %d", &a, &b)
		if a < 2 {
			a = 2
		}
		for c := a; c <= b; c++ {
			isPrime := true
			for _, num := range primes {
				if c != num && c%int(num) == 0 {
					isPrime = false
					break
				}
			}
			if isPrime {
				fmt.Println(c)
			}
		}
		fmt.Println()
	}
}
