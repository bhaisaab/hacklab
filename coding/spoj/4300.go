package main

import "fmt"

func binsearch(low, high, side, N int) int {
	m := (high + low) / 2
	if high-low < 2 {
		if high*side <= N {
			return high
		} else {
			if low*side <= N {
				return low
			}
			return low - 1
		}
	}
	if m*side > N {
		return binsearch(low, m, side, N)
	}
	return binsearch(m, high, side, N)
}

func main() {
	var N int
	fmt.Scanf("%d", &N)
	count := 0
	for i := 1; i <= N; i++ {
		count += (binsearch(i, N, i, N) - i + 1)
	}
	fmt.Println(count)
}
