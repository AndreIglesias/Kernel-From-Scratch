# GRUB Configuration File (`grub.cfg`)

The `grub.cfg` file is a configuration file used by GRUB (Grand Unified Bootloader) to load and manage different operating systems or kernels. This file specifies how GRUB should boot your custom kernel.

## Configuration Entry

```sh
menuentry "kernel-from-scratch" {
	multiboot /boot/kernel.bin
}
```

### Explanation

- **menuentry "kernel-from-scratch"**: This line defines a new menu entry in the GRUB bootloader. When GRUB is loaded, this entry will appear in the list of bootable options with the label "kernel-from-scratch".
  
  - `menuentry`: Keyword that starts a new boot menu entry.
  - `"kernel-from-scratch"`: The label that will be displayed in the GRUB menu for this boot option.

- **multiboot /boot/kernel.bin**: This line tells GRUB to load the specified kernel using the Multiboot protocol.

  - `multiboot`: Keyword that specifies the use of the Multiboot standard to load the kernel.
  - `/boot/kernel.bin`: Path to the kernel binary file that GRUB will load. This path is relative to the root of the GRUB filesystem, typically the root of the ISO or the partition where GRUB is installed.

## Usage

### Creating the `grub.cfg` File

1. **Directory Structure**: Ensure your ISO or bootable device has the necessary directory structure.

    ```sh
    mkdir -p iso/boot/grub
    ```

2. **Create `grub.cfg`**: Create the `grub.cfg` file inside the `iso/boot/grub` directory with the following content:

    ```sh
    # iso/boot/grub/grub.cfg
    menuentry "kernel-from-scratch" {
        multiboot /boot/kernel.bin
    }
    ```

3. **Copy Kernel Binary**: Ensure that the kernel binary (`kernel.bin`) is located in the `iso/boot/` directory.

    ```sh
    cp path/to/your/kernel.bin iso/boot/
    ```

### Building the Bootable ISO

1. **Generate ISO**: Use `grub-mkrescue` to create a bootable ISO image.

    ```sh
    grub-mkrescue -o my_kernel.iso iso
    ```

### Booting the Kernel with QEMU

1. **Run QEMU**: Use QEMU to boot the generated ISO image.

    ```sh
    qemu-system-i386 -cdrom my_kernel.iso
    ```

## Additional Notes

- **Multiboot Protocol**: The `multiboot` keyword in the `grub.cfg` file ensures that GRUB uses the Multiboot standard to load your kernel. This standard allows GRUB to pass information about the system to the kernel in a standardized way.
- **Customization**: You can customize the `grub.cfg` file to add more options or modify the behavior of the bootloader as needed.
