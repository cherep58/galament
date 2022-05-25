# syntax=docker/dockerfile:1
FROM gcc:9.4
RUN apt-get update \
    && apt-get -y install mc cmake libboost-all-dev libprotobuf-dev protobuf-compiler; exit 0
ENTRYPOINT tail -f /dev/null