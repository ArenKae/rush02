/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:01:33 by acosi             #+#    #+#             */
/*   Updated: 2023/02/03 11:31:48 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_format(va_list args, const char *str)
{
	int	count;

	count = 0;
	if (*str == 'c')
		count += write_char (va_arg(args, int));
	else if (*str == 's')
		count += write_str(va_arg(args, char *));
	else if (*str == 'p')
		count += write_ptr(va_arg(args, uintptr_t));
	else if (*str == 'd' || *str == 'i')
		count += write_nbr(va_arg(args, int));
	else if (*str == 'u')
		count += write_uint(va_arg(args, unsigned int));
	else if (*str == 'x')
		count += write_hex(va_arg(args, unsigned int), 0);
	else if (*str == 'X')
		count += write_hex(va_arg(args, unsigned int), 1);
	else if (*str == '%')
		count += write_percent();
	else
		return (-1);
	return (count);
}

/*The va_arg macro is used to get the next argument converted to the 
specified data type.*/

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			count += ft_format(args, str + 1);
			str++;
		}
		else
			count += write_char(*str);
		str++;
	}
	va_end(args);
	if (count < 0)
		return (-1);
	return (count);
}
