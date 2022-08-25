FROM debian:bullseye AS debsrc
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates \
    gnupg dpkg-dev 
COPY raspbian.list /etc/apt/sources.list.d/raspbian.list
RUN curl -sL https://archive.raspbian.org/raspbian.public.key | apt-key add -
WORKDIR /opt
RUN apt-get update && apt-get source libttspico-utils

FROM debian:bullseye 
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates \
    xz-utils clang lld cmake ninja-build \
    libtool libpopt-dev build-essential
COPY --from=debsrc /opt/svox-1.0+git20130326/pico/lib/ /libtts/


#ENV AR "/opt/wasi-sdk/bin/llvm-ar"
#ENV RANLIB "/opt/wasi-sdk/bin/llvm-ranlib"
#ENV LLVM_BIN "/usr/lib/llvm-*/bin"
ENV CC "clang"
COPY --from=debsrc /opt/svox-1.0+git20130326/pico/bin/ /libtts/bin/
COPY wasi.Makefile /libtts/Makefile 

RUN curl -L https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-16/wasi-sysroot-16.0.tar.gz | \
    tar x -zv -C /opt -f - 

RUN curl -sL https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-16/libclang_rt.builtins-wasm32-wasi-16.0.tar.gz | \
  tar x -zf - -C /usr/lib/llvm-11/lib/clang/11.0.1

COPY example.c /libtts/bin/
RUN cd /libtts && make


