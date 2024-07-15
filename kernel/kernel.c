/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:08:17 by ciglesia          #+#    #+#             */
/*   Updated: 2024/07/16 01:39:13 by ciglesia         ###   ########.fr       */
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

void kernel_main(void)
{
    t_terminal terminal;

	terminal_init(&terminal);
	gdt_init();
    printk(&terminal, "Hello, kernel World!\n%d\n\n", 42);
    printk(&terminal, "%s\n", "$$\\   $$\\  $$$$$$\\");
    printk(&terminal, "%s\n", "$$ |  $$ |$$  __$$\\");
    printk(&terminal, "%s\n", "$$ |  $$ |\\__/  $$ |");
    printk(&terminal, "%s\n", "$$$$$$$$ | $$$$$$  |");
    printk(&terminal, "%s\n", "\\_____$$ |$$  ____/");
    printk(&terminal, "%s\n", "      $$ |$$ |");
    printk(&terminal, "%s\n", "      $$ |$$$$$$$$\\");
    printk(&terminal, "%s\n", "      \\__|\\________|");
}
