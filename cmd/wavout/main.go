package main

import (
	"bufio"
	"os"

	tts "github.com/tzneal/gopicotts"
)

func main() {
	var opts = tts.DefaultOptions
	opts.LanguageDir = "./"
	opts.Language = tts.LanguageEnGB
	eng, err := tts.NewEngine(opts)
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
