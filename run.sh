#!/usr/bin/env bash

# if the file kernel.iso exists, run qemu-system-i386 -cdrom kernel.iso
if [ -f kernel.iso ]; then
    qemu-system-i386 -cdrom kernel.iso -m 512 -smp 2
else
    echo -e "\e[1mkernel.iso\e[0m not found. Run \e[1m./build.sh\e[0m first."
fi