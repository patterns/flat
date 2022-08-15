package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var counter uint
	var scanner = bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		counter += 1
		fmt.Printf("%d %s\n", counter, scanner.Text())
	}

	/*
	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}*/
}
