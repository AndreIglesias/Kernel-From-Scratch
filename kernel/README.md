# Kernel Development README

This project involves developing a simple kernel that runs on an x86 architecture. The kernel is capable of initializing the terminal and displaying text on the screen. This README provides an overview of the key components and functionality provided in the `kernel.h`, `kernel.c`, and `terminal.c` files, as well as instructions for compiling and running the kernel.

## Files Overview

### 1. `kernel.h`

The `kernel.h` header file defines the essential data structures, constants, and function prototypes used by the kernel.

#### Key Elements

- **Preprocessor Checks**:
  - Ensures the code is compiled with an ix86-elf cross-compiler.
  
  ```c
  #if defined(__linux__)
  # error "You are not using an ix86-elf compiler cross-compiler"
  #endif

  #if !defined(__i386__)
  # error "This kernel needs to be compiled with a ix86-elf compiler"
  #endif
  ```

- **Constants**:
  - Defines screen dimensions and VGA color constants.
  
  ```c
  #define VGA_WIDTH 80
  #define VGA_HEIGHT 25
  ```

- **VGA Colors Enumeration**:
  - Defines various color constants used for text mode.
  
  ```c
  enum e_vga_color {
      VGA_COLOR_BLACK = 0,
      VGA_COLOR_BLUE = 1,
      ...
      VGA_COLOR_WHITE = 15,
  };
  ```

- **Terminal Structure**:
  - Defines the `t_terminal` struct to manage terminal state.
  
  ```c
  typedef struct s_terminal {
      size_t row;
      size_t column;
      uint8_t color;
      uint16_t *buffer;
  } t_terminal;
  ```

- **Function Prototypes**:
  - Declares functions for terminal operations.
  
  ```c
  void terminal_putstr(const char *data, t_terminal *terminal);
  void terminal_putentryat(char c, t_terminal *terminal, size_t x, size_t y);
  ```

### 2. `kernel.c`

The `kernel.c` file contains the kernel's main logic, including terminal initialization and entry point definition.

#### Key Functions

- **VGA Entry Helpers**:
  - Functions to create VGA entries with specified character and color.
  
  ```c
  static inline uint8_t vga_entry_color(enum e_vga_color fg, enum e_vga_color bg) {
      return fg | bg << 4;
  }

  static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
      return (uint16_t) uc | (uint16_t) color << 8;
  }
  ```

- **Terminal Entry Function**:
  - Writes a character to the terminal at a specific position.
  
  ```c
  void terminal_putentryat(char c, t_terminal *terminal, size_t x, size_t y) {
      terminal->buffer[y * VGA_WIDTH + x] = vga_entry(c, terminal->color);
  }
  ```

- **Terminal Initialization**:
  - Initializes the terminal, setting up the screen with the default color and clearing it.
  
  ```c
  void terminal_init(t_terminal *terminal) {
      ...
      terminal->buffer = (uint16_t *)0xB8000;
      ...
  }
  ```

- **Kernel Main Function**:
  - The entry point of the kernel, which initializes the terminal and displays "42".
  
  ```c
  void kernel_main(void) {
      t_terminal terminal;
      terminal_init(&terminal);
      terminal_putstr("42", &terminal);
  }
  ```

### 3. `terminal.c`

The `terminal.c` file contains functions specifically for terminal operations, such as printing characters and strings.

#### Key Functions

- **Print Character**:
  - Prints a character to the terminal and handles line wrapping.
  
  ```c
  void terminal_putchar(char c, t_terminal *terminal) {
      ...
  }
  ```

- **Print String**:
  - Prints a string to the terminal.
  
  ```c
  void terminal_putstr(const char *data, t_terminal *terminal) {
      size_t i = 0;
      while (data[i]) {
          terminal_putchar(data[i++], terminal);
      }
  }
  ```

## Compilation and Running

### Requirements

- An ix86-elf cross-compiler.

### Steps

1. **Set Up the Project**:
   Ensure the directory structure is as follows:
   ```
   ├── boot
   │   └── boot.s
   ├── grub
   │   └── grub.cfg
   ├── include
   │   └── kernel.h
   ├── kernel
   │   ├── kernel.c
   │   └── terminal.c
   ├── linker
   │   └── linker.ld
   ├── Makefile
   └── obj
   ```

2. **Compile the Kernel**:
   Run the following command to compile the kernel and create the ISO:
   ```sh
   make
   ```

3. **Clean Build Artifacts**:
   To clean the object files, kernel binary, and ISO, run:
   ```sh
   make fclean
   ```

4. **Run the Kernel**:
   Use QEMU to boot the kernel:
   ```sh
   qemu-system-i386 -cdrom kernel.iso
   ```
