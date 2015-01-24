package secret

var signals = [...]struct {
	code   int
	signal string
}{
	{1, "wink"},
	{2, "double blink"},
	{4, "close your eyes"},
	{8, "jump"},
}

func Handshake(code int) []string {
	output := []string{}
	if code < 1 || code > 31 {
		return output
	}
	for _, run := range signals {
		if run.code&code != 0 {
			output = append(output, run.signal)
		}
	}
	if 16&code != 0 {
		size := len(output)
		for i := 0; i < size/2; i++ {
			output[i], output[size-i-1] = output[size-i-1], output[i]
		}
	}
	return output
}
