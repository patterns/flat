package main

import (
	"bufio"
	"os"
	"strings"
)
import "github.com/patterns/flat"

func main() {
	var b strings.Builder
	var scanner = bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		b.WriteString(scanner.Text())
	}
	if err := scanner.Err(); err != nil {
		//TODO capture detail
		return
	}
	var voice = flat.NewKal()
	w := flat.TextToWave(b.String(), voice)
	//TODO wav to stdout
	print(w)
}

