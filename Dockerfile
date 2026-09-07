FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    g++ \
    make \
    gdb \
    valgrind \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /taskforge

COPY . .

RUN make clean && make

CMD ["./taskforge"]
