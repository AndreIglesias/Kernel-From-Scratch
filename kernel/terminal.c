/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:02:08 by ciglesia          #+#    #+#             */
/*   Updated: 2024/07/14 13:57:02 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernel.h"

void	terminal_putchar(char c, t_terminal *terminal)
{
	terminal_putentryat(c, terminal, terminal->column, terminal->row);
	if (++terminal->column == VGA_WIDTH)
	{
		terminal->column = 0;
		if (++terminal->row == VGA_HEIGHT)
			terminal->row = 0;
	}
}

void	terminal_putstr(const char *data, t_terminal *terminal)
{
	size_t	i;

	i = 0;
	while (data[i])
		terminal_putchar(data[i++], terminal);
}
