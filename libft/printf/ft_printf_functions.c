/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:05:37 by acosi             #+#    #+#             */
/*   Updated: 2023/02/03 11:00:13 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	write_char(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	write_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (*str)
	{
		write_char(*str);
		str++;
		i++;
	}
	return (i);
}

int	write_percent(void)
{
	write(1, "%", 1);
	return (1);
}

int	write_ptr(uintptr_t p)
{
	char		buffer[sizeof(uintptr_t) * 2 + 3];
	int			i;
	const char	*hex_digits;

	hex_digits = "0123456789abcdef";
	i = sizeof(uintptr_t) * 2 + 2;
	buffer[i] = 0;
	if (p == 0)
	{
		buffer[--i] = '0';
		buffer[--i] = 'x';
		buffer[--i] = '0';
	}
	else
	{
		while (p)
		{
			buffer[--i] = hex_digits[p & 15];
			p >>= 4;
		}
		buffer[--i] = 'x';
		buffer[--i] = '0';
	}
	return (write_str(buffer + i));
}

/*uintptr_t = an unsigned integer type with the property that any valid pointer 
to void can be converted to this type, then converted back to pointer to void, 
and the result will compare equal to the original pointer.*/