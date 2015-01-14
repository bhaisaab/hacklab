package main

import "fmt"

func main() {

	cheat := [10][]int{
		[]int{0},
		[]int{1},
		[]int{2, 4, 8, 6},
		[]int{3, 9, 7, 1},
		[]int{4, 6},
		[]int{5},
		[]int{6},
		[]int{7, 9, 3, 1},
		[]int{8, 4, 2, 6},
		[]int{9, 1},
	}

	var t int
	fmt.Scanf("%d", &t)
	for ; t > 0; t-- {
		var base, index int
		fmt.Scanf("%d %d", &base, &index)
		if index == 0 {
			fmt.Println(1)
			continue
		}
		digit := base % 10
		l := len(cheat[digit])
		idx := (index - 1) % l
		fmt.Println(cheat[digit][idx])
	}
}
