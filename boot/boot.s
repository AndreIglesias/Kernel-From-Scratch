/* kernel entry point that sets up the processor environment */
/* https://wiki.osdev.org/Bare_Bones#Bootstrap_Assembly */

/* Declare constants for the multiboot header. */
.set ALIGN,    1 << 0             /* align loaded modules on page boundaries */
.set MEMINFO,  1 << 1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO    /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002         /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS)   /* checksum of above, to prove we are multiboot */

/* Multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Stack setup */
.section .bss
.align 16
.global stack_bottom
.global stack_top
stack_bottom:
.skip 16384    /* 16 KiB stack space */
stack_top:

/* Entry point */
.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp    /* Set up stack */

    call kernel_main        /* Enter high-level kernel */

    /* Infinite loop to halt the CPU */
    cli
1:  hlt
    jmp 1b

.size _start, . - _start
