# Kernel-From-Scratch
A kernel from scratch, without any existing software, API, or such.
![image](https://github.com/AndreIglesias/Kernel-From-Scratch/assets/35022933/1383b505-4bc2-49e6-82d6-d7fad83e572c)

## Setup

First, we will need KVM.

### KVM

> **KVM** ([Kernel-based Virtual Machine](https://ubuntu.com/blog/kvm-hyphervisor)) is the leading open source virtualisation technology for Linux. It installs natively on all Linux distributions and turns underlying physical servers into hypervisors so that they can host multiple, isolated virtual machines (VMs). KVM comes with no licenses, **type-1 hypervisor** capabilities and a variety of performance extensions

![alt text](media/kvm.png)

#### Dependencies Installation

```bash
sudo apt-get install -y bridge-utils cpu-checker libvirt-clients libvirt-daemon qemu qemu-kvm xorriso mtools
```

#### Check for Virtualization Support

```bash
kvm-ok
# Successful output:
# INFO: /dev/kvm exists
# KVM acceleration can be used
```
### Cross-Compiler

We need a [**Cross-Compiler**](../xcompiler/) to compile the operating system / kernel, as the **host** and **target** systems may differ in CPU, operating system, and/or executable format.

[![GCC compiler](media/gcc.png)](../xcompiler/README.md)

## Kernel Essentials

### Entry Point (`boot.s`)
Kernel entry point that sets up the processor environment.

The `boot.s` file is an assembly code file used as the bootloader for the kernel. It sets up the environment required by the kernel and provides the initial **entry point** for the kernel code. 


### Routines (`kernel.c`)
The actual kernel routines.

### Linker (`linker.ld`)
For linking the above files.