/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 00:34:03 by ciglesia          #+#    #+#             */
/*   Updated: 2024/07/16 01:02:39 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kernel.h"

void    terminal_itoa_base(uint32_t n, uint32_t base, t_terminal *terminal)
{
    const char *digits = "0123456789ABCDEF";
    uint32_t    div = 1;

    while (div * base < n && div * base > div)
        div *= base;
    while (div)
    {
        terminal_putchar(digits[n / div], terminal);
        n %= div;
        div /= base;
    }
}

void    printk(t_terminal *terminal, const char *s, ...)
{
    va_list args;
    uint32_t i;

    va_start(args, s);
    i = 0;
    while (s[i])
    {
        if (s[i] != '%')
        {
            terminal_putchar(s[i++], terminal);
            continue ;
        }
        i++;
        if (s[i] == '%')
            terminal_putchar(s[i], terminal);
        else if (s[i] == 'c')
            terminal_putchar(va_arg(args, int), terminal);
        else if (s[i] == 's')
            terminal_putstr(va_arg(args, char *), terminal);
        else if (s[i] == 'd' || s[i] == 'i')
            terminal_itoa_base(va_arg(args, int), 10, terminal);
        else if (s[i] == 'u')
            terminal_itoa_base(va_arg(args, uint32_t), 10, terminal);
        else if (s[i] == 'x')
        {
            terminal_putstr("0x", terminal);
            terminal_itoa_base(va_arg(args, uint32_t), 16, terminal);
        }
        else if (s[i] == 'b')
        {
            terminal_putstr("0b", terminal);
            terminal_itoa_base(va_arg(args, uint32_t), 2, terminal);
        }
        i++;
    }
    va_end(args);
}