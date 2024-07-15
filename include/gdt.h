/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 22:29:36 by ciglesia          #+#    #+#             */
/*   Updated: 2024/07/15 23:55:17 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GDT_H
# define GDT_H

# include "kernel.h"

# define GDT_ADDRESS	0x00000800
# define GDT_ENTRIES	7

// Access & Flag options
# define HIGH 0
# define MEDIUM 1
# define LOW 2
# define CODE_DATA 1

// Access byte
# define A_PRESENT(X)    (X << 7)
# define A_PRIVILEGE(X)  (X << 5)
# define A_TYPE(X)       (X << 4)
# define A_EXECUTABLE(X) (X << 3)
# define A_DIRECTION(X)  (X << 2)
# define A_READWRITE(X)  (X << 1)
# define A_ACCESSED(X)   (X << 0)

// Flags
# define F_GRANULARITY(X) (X << 3)
# define F_SIZE(X)        (X << 2)
# define F_LONG(X)        (X << 1)
# define F_AVAIL(X)       (X << 0)

// Segment access byte
# define ACCESS_KERNEL A_PRESENT(1) | A_PRIVILEGE(HIGH) | A_TYPE(CODE_DATA)
# define ACCESS_USER   A_PRESENT(1) | A_PRIVILEGE(LOW)  | A_TYPE(CODE_DATA)

# define ACCESS_CODE    A_EXECUTABLE(1) | A_DIRECTION(0) | A_READWRITE(1) | A_ACCESSED(0)
# define ACCESS_DATA    A_EXECUTABLE(0) | A_DIRECTION(0) | A_READWRITE(1) | A_ACCESSED(0)
# define ACCESS_STACK   A_EXECUTABLE(0) | A_DIRECTION(1) | A_READWRITE(1) | A_ACCESSED(0)

// Segment flags
# define GDT_FLAGS F_GRANULARITY(1) | F_SIZE(1) | F_LONG(0) | F_AVAIL(0) 

// Global Descriptor Table (GDT) entry
typedef struct s_gdt {
	uint16_t limit_low;    // 16 bits of limit
	uint16_t base_low;     // 16 bits of base
	uint8_t base_mid;      // 8 bits of base
	uint8_t access;        // 8 bits off access byte
	uint8_t limit_high :4; // 4 bits of limit
	uint8_t flags :4;      // 4 bits of flags
	uint8_t base_high;     // last 8 bits of base
} __attribute__((packed)) t_gdt;

// Pointer to the GDT
typedef struct s_gdtptr {
    uint16_t limit;        // 16 bits of limit
    uint32_t base;         // 32 bits of base
} __attribute__((packed)) t_gdtptr;


extern void load_gdt(uint32_t gdt_ptr);

extern t_gdt    gdt[GDT_ENTRIES];
extern t_gdtptr *gdtptr;

#endif