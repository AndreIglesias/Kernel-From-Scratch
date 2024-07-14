# Linker (`linker.ld`)

## Purpose of the Linker Script

The linker script is a critical component in the process of compiling and linking a kernel. It defines how the sections of object files are organized in the final executable image. This organization ensures that the bootloader correctly identifies and loads the kernel, and that the kernel runs as intended.

## Key Sections and Symbols

### Entry Point

The `ENTRY(_start)` directive tells the linker that `_start` is the entry point of the kernel. The bootloader will transfer control to this symbol when starting the kernel.

```ld
ENTRY(_start)
```

### Sections

The `SECTIONS` command in the linker script defines how different sections of the object files are placed in memory.

```ld
SECTIONS
{
    . = 1M;
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
```

### Explanation of Sections

#### `. = 1M;`

The starting address for the kernel is set to 1 MiB (0x100000). This is a conventional location for kernels to be loaded by the bootloader, particularly in older BIOS systems.

```ld
. = 1M;
```

#### `.text`

The `.text` section contains the executable code. It starts with the multiboot header, followed by the kernel’s code.

```ld
.text BLOCK(4K) : ALIGN(4K)
{
    *(.multiboot)
    *(.text)
}
```

- `BLOCK(4K)`: Aligns the section to a 4 KiB boundary.
- `ALIGN(4K)`: Ensures the section starts at a 4 KiB aligned address.
- `*` specifies all files' sections named `.multiboot` and `.text`.

#### `.rodata`

The `.rodata` section contains read-only data, such as constants and string literals.

```ld
.rodata BLOCK(4K) : ALIGN(4K)
{
    *(.rodata)
}
```

- `BLOCK(4K)` and `ALIGN(4K)`: Similar to `.text`, ensures alignment to 4 KiB.

#### `.data`

The `.data` section contains initialized read-write data.

```ld
.data BLOCK(4K) : ALIGN(4K)
{
    *(.data)
}
```

- `BLOCK(4K)` and `ALIGN(4K)`: Ensures alignment to 4 KiB.

#### `.bss`

The `.bss` section contains uninitialized data and is used for the stack. This section is zeroed out at runtime.

```ld
.bss BLOCK(4K) : ALIGN(4K)
{
    *(COMMON)
    *(.bss)
}
```

- `BLOCK(4K)` and `ALIGN(4K)`: Ensures alignment to 4 KiB.
- `*(COMMON)`: Includes common symbols.
- `*` specifies all files' sections named `.bss`.

### Additional Sections

If the compiler generates additional sections, they will be included in segments with the same name. Modify the script to accommodate these as needed.

## Summary

This linker script ensures that the kernel is loaded at the correct memory address and that its various sections (code, read-only data, initialized data, uninitialized data) are properly aligned and placed. Understanding this script is essential for developing and debugging the kernel.
