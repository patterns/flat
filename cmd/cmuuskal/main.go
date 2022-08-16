package main

import (
	"bufio"
	"fmt"
	"os"
)
import "github.com/patterns/flat"

func main() {
	test := flat.NewKal()
	fmt.Printf("DEBUG %s\n", test)
	var scanner = bufio.NewScanner(os.Stdin)
	for scanner.Scan() {

		fmt.Printf(" %s\n", scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		return
	}
}

