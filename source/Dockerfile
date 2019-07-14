FROM ubuntu:latest
RUN \
    apt-get update && \
    apt-get install -y \
        build-essential \
        qt5-default \
        qt5-qmake && \
    rm -rf /var/lib/apt/lists/*

ADD . /huwcode
WORKDIR /huwcode

RUN qmake -o Makefile source/HuwInterpreter.pro -spec linux-g++
RUN make

# ----

FROM alpine:latest
COPY --from=0 /huwcode/HuwInterpreter /usr/bin/HuwInterpreter
RUN ln -s /usr/bin/HuwInterpreter /usr/bin/huwcode
