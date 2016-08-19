package main
import (
	"fmt"
	"os"
	"bufio"
	"strconv"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	for {
		s, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		i, _ := strconv.Atoi(s[:len(s)-1])
		if i == 42 {
			break
		}
		fmt.Println(i)
	}
}
