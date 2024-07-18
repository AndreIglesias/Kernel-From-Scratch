/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:08:17 by ciglesia          #+#    #+#             */
/*   Updated: 2024/07/16 10:51:12 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernel.h"

static inline uint8_t	vga_entry_color(
	enum e_vga_color fg,
	enum e_vga_color bg
	)
{
	return (fg | bg << 4);
}

static inline uint16_t	vga_entry(unsigned char uc, uint8_t color)
{
	return ((uint16_t) uc | (uint16_t) color << 8);
}

void	terminal_putentryat(char c, t_terminal *terminal, size_t x, size_t y)
{
	terminal->buffer[y * VGA_WIDTH + x] = vga_entry(c, terminal->color);
}

void	terminal_init(t_terminal *terminal)
{
	size_t	y;
	size_t	x;
	size_t	index;

	terminal->row = 0;
	terminal->column = 0;
	terminal->color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal->buffer = (uint16_t *)0xB8000;
	y = 0;
	while (y < VGA_HEIGHT)
	{
		x = 0;
		while (x < VGA_WIDTH)
		{
			index = y * VGA_WIDTH + x;
			terminal->buffer[index] = vga_entry(' ', terminal->color);
			x++;
		}
		y++;
	}
}

// Assuming a 3 GHz processor
void sleep_half_second() {
    const uint64_t cycles_per_half_second = 150000000;
    uint64_t start, end;

    asm volatile ("rdtsc" : "=A" (start));
    do {
        asm volatile ("rdtsc" : "=A" (end));
    } while ((end - start) < cycles_per_half_second);
}

void print_stack(t_terminal *terminal)
{
    uint32_t* stack_ptr;
    uint32_t* stack_end;

    stack_ptr = &stack_top;
    stack_end = &stack_bottom;
    int i = 0;
    while (stack_ptr >= stack_end)
    {
        printk(terminal, "%d %x: %x       \n", i++, (uint32_t)stack_ptr, *stack_ptr);
        stack_ptr--;
        sleep_half_second();
    }
    // Stack is from, to, size of stack
    printk(terminal, "Stack: top(%x), bottom(%x), size(%d)\n", 
        &stack_top, &stack_bottom, &stack_top - &stack_bottom);
}

void kernel_main(void)
{
    t_terminal terminal;

	terminal_init(&terminal);
	gdt_init();
    printk(&terminal, "Hello, kernel World!\n%d\n\n", 42);
    printk(&terminal, "                              %s\n", "$$\\   $$\\  $$$$$$\\");
    printk(&terminal, "                              %s\n", "$$ |  $$ |$$  __$$\\");
    printk(&terminal, "                              %s\n", "$$ |  $$ |\\__/  $$ |");
    printk(&terminal, "                              %s\n", "$$$$$$$$ | $$$$$$  |");
    printk(&terminal, "                              %s\n", "\\_____$$ |$$  ____/");
    printk(&terminal, "                              %s\n", "      $$ |$$ |");
    printk(&terminal, "                              %s\n", "      $$ |$$$$$$$$\\");
    printk(&terminal, "                              %s\n", "      \\__|\\________|");
    print_stack(&terminal);
}
