
FROM debian:bullseye AS debsrc
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates\
     dpkg-dev gnupg
WORKDIR /opt
RUN echo "deb-src http://archive.raspbian.org/raspbian bullseye main contrib non-free rpi"\
    > /etc/apt/sources.list.d/deb.list
RUN curl -sL https://archive.raspbian.org/raspbian.public.key | apt-key add -
RUN apt-get update && apt-get source libttspico-utils
RUN curl -o /tmp/bazel-5.3.0 -sL https://github.com/bazelbuild/bazel/releases/download/5.3.0/bazel-5.3.0-linux-arm64
RUN chmod a+x /tmp/bazel-5.3.0
# stage libpico.a
FROM debian:bullseye AS libpico
ENV DEBVER svox-1.0+git20130326
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential 
COPY --from=debsrc /opt/${DEBVER}/pico /opt/pico
RUN cd /opt/pico/lib && gcc -fPIC -g -c *.c && ar rcs libpico.a *.o

# final stage
FROM golang:1.19.0-bullseye
RUN apt-get update && apt-get install -y --no-install-recommends patch
COPY --from=debsrc /tmp/bazel-5.3.0 /bin/bazel
COPY . /myapp
COPY --from=libpico /opt/pico/lib/ /myapp/lib/

# bazelisk run //:gazelle
# bazelisk run //:gazelle-update-repos
# bazelisk build //...
