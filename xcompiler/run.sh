#!/bin/env bash

docker build . -t xcompiler && docker run -it xcompiler /bin/bash
