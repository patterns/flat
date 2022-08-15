FROM golang:1.19.0-bullseye
RUN go install github.com/bazelbuild/bazelisk@latest

WORKDIR /opt
RUN wget --quiet https://github.com/tinygo-org/tinygo/releases/download/v0.25.0/tinygo_0.25.0_arm64.deb
RUN dpkg -i tinygo_0.25.0_arm64.deb
COPY . /myapp

#RUN rm tinygo_0.25.0_arm64.deb ;\
#    go mod init example.com/test ;\
#    go mod tidy ;\
#    tinygo build -o hello.wasm -target=wasi -wasm-abi=generic -gc=leaking -no-debug main.go

##ENTRYPOINT ["/entrypoint.sh"]

# bazelisk run //:gazelle
# bazelisk build //...
