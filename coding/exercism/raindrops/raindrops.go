package raindrops

import "strconv"

var drops = []struct {
	prime int
	text  string
}{
	{3, "Pling"},
	{5, "Plang"},
	{7, "Plong"},
}

func Convert(input int) string {
	var output string

	for _, drop := range drops {
		if input%drop.prime == 0 {
			output += drop.text
		}
	}

	if len(output) == 0 {
		return strconv.Itoa(input)
	}
	return output
}
