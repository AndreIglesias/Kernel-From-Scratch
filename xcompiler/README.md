# GCC Cross-Compiler

A **cross-compiler** is a type of compiler that runs on one architecture or operating system (the **host**) but produces executable code for a different architecture or operating system (the **target**). This is in contrast to a native compiler, which compiles code for the same platform on which it runs.

[![GCC compiler](../docs/media/gcc.png)](../xcompiler/README.md)

## Setup

To [Setup the Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler), we've created a [`Dockerfile`](Dockerfile).

It can be built and ran with the `run.sh` script or like this:

```bash
docker build . -t xcompiler && docker run -it xcompiler
```

## Usage

```bash
TARGET="i686-elf"
/opt/cross/bin/$TARGET-gcc --version
# Or
/opt/cross/bin/i686-elf-gcc --version
```
