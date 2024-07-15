/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:34:11 by ciglesia          #+#    #+#             */
/*   Updated: 2024/07/15 23:54:36 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gdt.h"

t_gdt    gdt[GDT_ENTRIES];
t_gdtptr *gdtptr = (t_gdtptr *)GDT_ADDRESS;

void    create_descriptor(uint16_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    // Split the base into the 3 parts
    gdt[index].base_low = (base & 0xFFFF);
    gdt[index].base_mid = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    // Split the limit into the 2 parts
    gdt[index].limit_low = (limit & 0xFFFF);
    gdt[index].limit_high = (limit >> 16) & 0x0F;

    // Set the flags and access
    gdt[index].flags = (flags & 0x0F);

    gdt[index].access = access;
}

void    gdt_init(void)
{
    // Store table address in ptr struct
    gdtptr->limit = (sizeof(t_gdt) * GDT_ENTRIES) - 1;
    gdtptr->base = (uint32_t)&gdt;

    create_descriptor(0, 0, 0, 0, 0); // Null segment
    create_descriptor(1, 0, 0xFFFFF, ACCESS_KERNEL | ACCESS_CODE, GDT_FLAGS); // Kernel Code segment
    create_descriptor(2, 0, 0xFFFFF, ACCESS_KERNEL | ACCESS_DATA, GDT_FLAGS); // Kernel Data segment
    create_descriptor(3, 0, 0xFFFFF, ACCESS_KERNEL | ACCESS_STACK, GDT_FLAGS); // Kernel Stack segment
    create_descriptor(4, 0, 0xFFFFF, ACCESS_USER | ACCESS_CODE, GDT_FLAGS); // User Code segment
    create_descriptor(5, 0, 0xFFFFF, ACCESS_USER | ACCESS_DATA, GDT_FLAGS); // User Data segment
    create_descriptor(6, 0, 0xFFFFF, ACCESS_USER | ACCESS_STACK, GDT_FLAGS); // User Stack segment
    // Load the GDT
    load_gdt((uint32_t)gdtptr);    
}
