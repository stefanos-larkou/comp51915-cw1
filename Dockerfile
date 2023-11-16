FROM ubuntu:latest

RUN apt-get update && apt-get install git g++ cmake make docker -y

WORKDIR app

COPY . .

RUN [ -d "googletest" ] || rm -rf googletest
RUN git clone https://github.com/google/googletest.git

RUN [ -d "build" ] || rm -rf build
RUN mkdir build

WORKDIR build

RUN cmake ../sim
RUN make

WORKDIR ..

RUN chmod +x ./app.sh && chmod +x ./build/gs && chmod +x ./build/tests/tests

CMD ["./app.sh"]
