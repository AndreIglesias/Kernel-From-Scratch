/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 10:14:13 by ciglesia          #+#    #+#             */
/*   Updated: 2024/07/16 10:50:50 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

# if defined(__linux__)
#  error "You are not using an ix86-elf compiler cross-compiler"
# endif

# if !defined(__i386__)
#  error "This kernel needs to be compiled with a ix86-elf compiler"
# endif

# define VGA_WIDTH 80
# define VGA_HEIGHT 25

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
#include <stdarg.h>

/* Hardware text mode color constants. */
enum e_vga_color
{
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

typedef struct s_terminal
{
	size_t		row;
	size_t		column;
	uint8_t		color;
	uint16_t	*buffer;
}	t_terminal;

// Symbols from boot.s
extern uint32_t stack_bottom;
extern uint32_t stack_top;

void    gdt_init(void);

void	terminal_putchar(char c, t_terminal *terminal);
void	terminal_putstr(const char *data, t_terminal *terminal);
void	terminal_putentryat(char c, t_terminal *terminal, size_t x, size_t y);
void	printk(t_terminal *terminal, const char *s, ...);

#endif