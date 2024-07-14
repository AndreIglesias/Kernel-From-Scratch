#!/usr/bin/env bash

if [ $# -gt 0 ]; then
    ARGS="$@"
else
    ARGS="all"
fi

docker run -it -v "$PWD":/workspace xcompiler bash -c "make $ARGS"
