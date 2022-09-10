# flat

Learning Bazel mono repos by porting the
 [line tutorial](https://blog.cloudflare.com/running-zig-with-wasi-on-cloudflare-workers/)
 to Golang

## Quickstart
Generate BUILD files
```bash
bazelisk run //:gazelle
```

Build binaries
```bash
bazelisk build //...
```

Make WASM target
```bash
tinygo build -o hello.wasm -target=wasi -gc=leaking -no-debug cmd/stdout/*.go
```

## Credits

[bazel wasm protobuf](https://maori.geek.nz/a-web-app-using-bazel-golang-wasm-and-proto-c020914f4341)

[bazel embed](https://github.com/bazelbuild/rules_go/blob/master/docs/go/core/embedding.md)

[bazel cgo](https://blog.modest-destiny.com/posts/building-golang-cgo-with-bazel/)

[gopicotts by Todd Neal](https://github.com/tzneal/gopicotts)

[pico-tts by Michael Clark](https://github.com/Iiridayn/pico-tts)

[Cloudflare WASI](https://blog.cloudflare.com/running-zig-with-wasi-on-cloudflare-workers/)

[Bazel and Go](https://www.tweag.io/blog/2021-09-08-rules_go-gazelle/)

[Bazel and Android](https://docs.bazel.build/versions/2.0.0/tutorial/android-app.html)

