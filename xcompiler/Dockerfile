FROM ubuntu:focal
# Setup of a cross-compiler for i386-elf
# https://wiki.osdev.org/GCC_Cross-Compiler

ENV PREFIX="/opt/cross"
ENV TARGET="i386-elf"
ENV PATH="$PREFIX/bin:$PATH"
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y wget \
    build-essential bison flex libgmp3-dev grub2\
    libmpc-dev libmpfr-dev texinfo xorriso libisl-dev

WORKDIR /opt

# https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
# https://ftp.gnu.org/gnu/gcc/gcc-12.4.0/gcc-12.4.0.tar.xz

# Download and extract binutils
RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz \
    && tar -xf binutils-2.42.tar.xz \
    && cd binutils-2.42 \
    && mkdir build && cd build \
    && ../configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror \
    && make -j$(nproc) && make install \
    && cd ../.. && rm binutils-2.42.tar.xz

# Download and extract gcc
RUN wget https://ftp.gnu.org/gnu/gcc/gcc-12.4.0/gcc-12.4.0.tar.xz \
    && tar -xf gcc-12.4.0.tar.xz \
    && cd gcc-12.4.0 \
    && mkdir build && cd build \
    && ../configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers \
    && make all-gcc -j$(nproc) && make all-target-libgcc -j$(nproc) && make install-gcc && make install-target-libgcc \
    && cd ../.. && rm gcc-12.4.0.tar.xz

WORKDIR /workspace
