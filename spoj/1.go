package main

import (
	"fmt"
	"os"
)

func main() {
	var num int
	for {
		_, err := fmt.Scanf("%d", &num)
		if err != nil {
			fmt.Fprintln(os.Stderr, "Scanf error", err.Error())
		}
		if num == 42 {
			break
		}
		fmt.Println(num)
	}
}
