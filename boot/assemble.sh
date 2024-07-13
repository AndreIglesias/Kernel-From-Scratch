#!/usr/bin/env bash

if [ ! -z "$1" ]; then
    abs_path=$(realpath "$1")
    dir_path=$(dirname "$abs_path")
    file_name=$(basename "$1")
    output_file="${dir_path}/boot.o"

    docker run -it -v "$dir_path":/mnt xcompiler bash -c "/opt/cross/bin/i686-elf-as /mnt/$file_name -o /mnt/boot.o"
    echo "Assembled boot.o is located at: $output_file"
else
    echo "Usage: ./assemble.sh <boot.s>"
fi
