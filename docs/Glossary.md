# Kernel Development Glossary

This glossary provides definitions for key concepts required to develop a kernel in C, as described in the "*Kernel from Scratch*" project.

| Term                | Definition |
|---------------------|------------|
| **KVM (Kernel-based Virtual Machine)** | A virtualization module in the Linux kernel that allows the kernel to function as a hypervisor. KVM requires a userspace program like QEMU to provide full virtualization capabilities, such as managing virtual machines and emulating hardware. |
| **Linking**         | The process of combining various pieces of code and data into a single executable file. In kernel development, custom linker scripts are often required. |
| **ld (GNU Linker)** | The GNU linker, a tool that combines object files produced by a compiler into a single executable, library, or another "object" file. Custom `.ld` files are used to control the layout of the binary. |
| **GRUB (Grand Unified Bootloader)** | A bootloader package that supports multiple operating systems on a computer. It is used to load and transfer control to the kernel at startup. |
| **Bootloader**      | A small program that loads the operating system into memory when the computer starts. For this project, GRUB is used as the bootloader. |
| **ASM (Assembly Language)** | A low-level programming language that is closely related to machine code instructions. Used in kernel development for writing critical sections of code. |
| **Compiler Flags**  | Options passed to the compiler to control the compilation process. For kernel development, specific flags ensure that no standard libraries or startup files are linked. Examples include `-fno-builtin`, `-nostdlib`, etc. |
| **i386 Architecture** | A 32-bit microprocessor architecture also known as x86. This project targets the i386 architecture for compatibility and simplicity. |
| **Virtual Image**   | A file that contains a complete copy of a virtual machine's disk drive. It is used to run the kernel in a virtualized environment for testing. |
| **Emulation**       | Running software on a virtual machine that mimics the hardware of another system. KVM is recommended for emulating the kernel environment. |
| **Kernel**          | The core part of an operating system, responsible for managing system resources, hardware, and communication between software and hardware. |
| **Kernel Library**  | A set of basic functions and types that are part of the kernel, used for fundamental operations such as memory management and I/O operations. |
| **Multiboot Header**| A standard used by GRUB to load various kernels. It contains information that the bootloader uses to load the kernel properly. |
| **Linker Script**   | A file that provides the linker with instructions on how to combine and place the output sections of the final executable. Custom linker scripts are used in kernel development to control memory layout. |
| **Screen I/O Interface** | The part of the kernel that handles input and output operations to and from the screen, such as printing text. |
| **Scroll and Cursor Support** | Enhancements to the I/O interface that allow text to scroll and the cursor to be positioned correctly on the screen. |
