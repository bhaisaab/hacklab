package foodchain

import (
	"bytes"
	"fmt"
)

const TestVersion = 1

var animals = [...]struct {
	animal   string
	extended string
}{
	{"", ""},
	{"fly", ""},
	{"spider", "It wriggled and jiggled and tickled inside her.\n"},
}

func Verse(v int) string {
	var b bytes.Buffer
	if v == 0 {
		return ""
	}
	animal := animals[v].animal
	b.WriteString(fmt.Sprintf("I know an old lady who swallowed a %s.\n", animal))
	if animal != "horse" {

		b.WriteString(fmt.Sprintf("I don't know why she swallowed the %s. Perhaps she'll die.", animal))
	} else {
		b.WriteString("She's dead, of course!")
	}
	return b.String()

}

func Verses(i, j int) string {

}

func Song() string {

}
