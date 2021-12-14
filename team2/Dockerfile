FROM ubuntu:latest
EXPOSE 50051

COPY . /root/
WORKDIR /root/

# 安装依赖库
RUN apt update  && apt install -y build-essential autoconf libtool pkg-config && apt install libssl-dev && apt install git

# 安装cmake
RUN cd lib/cmake \
    && tar -zxvf cmake-3.22.0.tar.gz \
    && cd ./cmake-3.22.0 \
    && ./bootstrap \
    && make \
    && make install \
    && cd .. \
    && rm -rf cmake \
    && cd ..


# 安装grpc
RUN git clone git clone --recurse-submodules -b v1.42.0 https://github.com/grpc/grpc \
    && mkdir ./grpc/cmake/build \
    && cd ./grpc/cmake/build \
    && cmake ../.. \
    && make \
    && make install \
    && cd ../../.. 

# 安装Hiredis
RUN cd ./lib/hiredis && make && make install && cd ../..


# 编译项目
RUN mkdir build && cd build && cmake .. && make basicInfo && cd ..
# RUN mkdir build && cd build && cmake .. && make mall && cd ..
# RUN mkdir build && cd build && cmake .. && make seckill && cd ..

CMD ["./basicInfo"]
# CMD [ "./mall" ]
# CMD [ "./seckill" ]

LABEL Name=team2Application Version=0.0.1
