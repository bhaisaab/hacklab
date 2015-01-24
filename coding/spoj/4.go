package main

import "fmt"

type Node struct {
	value string
	next  *Node
}

type Stack struct {
	size int
	top  *Node
}

func NewStack() *Stack {
	return &Stack{0, nil}
}

func (s *Stack) Len() int {
	return s.size
}

func (s *Stack) Push(value string) {
	s.top = &Node{value, s.top}
	s.size++
}

func (s *Stack) Peek() string {
	if s.size > 0 {
		return s.top.value
	}
	return ""
}

func (s *Stack) Pop() string {
	if s.size > 0 {
		value := s.top.value
		s.top = s.top.next
		s.size--
		return value
	}
	return ""
}

func main() {
	stack := NewStack()

	var t int
	fmt.Scanf("%d", &t)
	var expr string
	for ; t > 0; t-- {
		fmt.Scanf("%s", &expr)
		for _, chr := range expr {
			c := string(chr)
			switch c {
			case "(":
				stack.Push(c)
			case ")":
				for {
					if stack.Len() < 1 {
						break
					}
					if stack.Peek() == "(" {
						stack.Pop()
						break
					}
					fmt.Print(stack.Pop())
				}
			case "+", "-", "*", "/", "^":
				stack.Push(c)
			default: //characters
				fmt.Print(c)
			}
		}
		fmt.Println()
	}
}
