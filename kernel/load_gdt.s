.global load_gdt    /* Allows the C code to call load_gdt() */

load_gdt:
    mov 4(%esp), %eax  /* Get the pointer to the GDT, passed as a parameter */
    lgdt (%eax)        /* Load the new GDT pointer */

    mov $0x10, %ax     /* 0x10 is the offset in the GDT to our data segment */
    mov %ax, %ds       /* Load all data segment selectors */
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ljmp $0x08, $.flush  /* 0x08 is the offset to our code segment: Far jump! */
.flush:
    ret
