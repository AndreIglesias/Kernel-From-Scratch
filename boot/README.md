# Bootloader Assembly File (`boot.s`)

The `boot.s` file is an assembly code file used as the bootloader for the kernel. It sets up the environment required by the kernel and provides the initial **entry point** for the kernel code. 

We are using the GNU assembler, which is part of our [cross-compiler toolchain](../xcompiler/).

## Build

Build with the [cross-compiler](../xcompiler/), running inside the Docker container:
```bash
i386-elf-as boot.s -o boot.o
```
Or using the `assemble.sh`:
```bash
./assemble.sh boot.s
# Output:
# Assembled boot.o is located at: /path/to/boot.o
```

## Multiboot Header

The very most important piece to create is the Multiboot header, as it must be very early in the kernel binary, or the bootloader will fail to recognize us.

The Multiboot header is used by the bootloader (e.g., GRUB) to identify and load the kernel. It contains magic numbers and flags defined by the Multiboot standard.

```asm
/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* 
Declare a multiboot header that marks the program as a kernel. These are magic
values that are documented in the multiboot standard.
*/
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
```

### Explanation

- **ALIGN**: Ensures that loaded modules are aligned on page boundaries.
- **MEMINFO**: Requests a memory map from the bootloader.
- **FLAGS**: Combines the above flags.
- **MAGIC**: A magic number (`0x1BADB002`) that identifies the file as a Multiboot-compliant kernel.
- **CHECKSUM**: A checksum to verify the validity of the Multiboot header.

## Stack Setup

The kernel requires a stack to function properly. This section allocates space for the stack.

```asm
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
```

### Explanation

- **stack_bottom**: Marks the beginning of the stack.
- **stack_top**: Marks the end of the stack.
- The stack is aligned to 16 bytes and 16 KiB of space is allocated for it.

## Entry Point

The entry point `_start` is where execution begins. This sets up the initial environment and transfers control to the kernel's main function.

```asm
.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp        /* Set up the stack pointer */

	call kernel_main            /* Enter the high-level kernel */

	cli                         /* Disable interrupts */
1:	hlt                         /* Halt the CPU */
	jmp 1b                      /* Infinite loop */
```

### Explanation

- **`mov $stack_top, %esp`**: Sets the stack pointer to the top of the allocated stack.
- **`call kernel_main`**: Calls the kernel's main function, `kernel_main`.
- **`cli`**: Disables interrupts to prevent any interrupt handling.
- **`hlt`**: Halts the CPU, putting it in a low-power state.
- **`jmp 1b`**: Jumps back to the `hlt` instruction, creating an infinite loop to keep the CPU halted.

## Size Definition

Defines the size of the `_start` symbol for debugging and call tracing purposes.

```asm
.size _start, . - _start
```

### Explanation

- **`.size _start, . - _start`**: Sets the size of the `_start` symbol to the difference between the current location and the start of the `_start` label.
