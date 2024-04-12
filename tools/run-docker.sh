#!/usr/bin/env sh

 docker run -it --rm \
-v $PWD:/workspace \
--name builder_cpp gitlab.siilicloud.com:5050/automotive/containers/cpp-builder:latest
