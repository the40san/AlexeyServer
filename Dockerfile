FROM ubuntu:16.04

RUN apt-get update -y && apt-get install -y make cmake g++5 git

RUN mkdir /install
WORKDIR /install
# INSTALL MESSAGE PACK
RUN git clone https://github.com/msgpack/msgpack-c.git
WORKDIR msgpack-c
RUN cmake -DMSGPACK_CXX11=ON . && make && make install

# INSTALL cpp_redis
WORKDIR /install
RUN git clone https://github.com/Cylix/cpp_redis.git
WORKDIR cpp_redis
RUN git submodule init && git submodule update && mkdir build
WORKDIR build
RUN cmake ../ && make && make install

COPY . /alexey
WORKDIR /alexey/src
RUN mkdir __build
WORKDIR __build
RUN cmake ../ && make
CMD ./main
