#!/bin/env bash

docker build . -t xcompiler && docker run -it --rm -v $(dirname $PWD):/workspace xcompiler /bin/bash
