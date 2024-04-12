#!/usr/bin/env sh

sudo docker run -it --rm \
-v $PWD:/workspace \
--name builder_cpp gitlab.siilicloud.com:5050/automotive/containers/cpp-builder:1.0.0
