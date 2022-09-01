package main

import (
	"bufio"
	"os"

	"github.com/tzneal/gopicotts"
)

func main() {
	var opts = gopicotts.DefaultOptions
	opts.LanguageDir = "./"
	eng, err := gopicotts.NewEngine(opts)
	defer eng.Close()

	if err != nil {
		panic(err)
	}
	//TODO stdout (wav headers)
	eng.SetFileOutput("testpico.wav")

        var scanner = bufio.NewScanner(os.Stdin)
        for scanner.Scan() {
		eng.SendText(scanner.Text())
        }

	eng.FlushSendText()
	eng.CloseFileOutput()
}
