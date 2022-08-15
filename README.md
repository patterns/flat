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

[Cloudflare WASI](https://blog.cloudflare.com/running-zig-with-wasi-on-cloudflare-workers/)

[Bazel and Go](https://www.tweag.io/blog/2021-09-08-rules_go-gazelle/)

[Bazel and Android](https://docs.bazel.build/versions/2.0.0/tutorial/android-app.html)
