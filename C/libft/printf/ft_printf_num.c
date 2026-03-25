/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:10:49 by acosi             #+#    #+#             */
/*   Updated: 2023/02/03 08:50:51 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	write_nbr(int value)
{
	if (value == -2147483648)
		return (write_str("-2147483648"));
	if (value < 0)
	{
		write_char('-');
		return (1 + write_nbr(-value));
	}
	if (value >= 10)
		return (write_nbr(value / 10) + write_nbr(value % 10));
	write_char(value + '0');
	return (1);
}

int	write_uint(unsigned int value)
{
	if (value >= 10)
		return (write_uint(value / 10) + write_uint(value % 10));
	write_char(value + '0');
	return (1);
}

int	write_hex(unsigned int value, int uppercase)
{
	char		buffer[sizeof(unsigned int) * 2 + 1];
	int			i;
	const char	*hex_digits;

	i = sizeof(unsigned int) * 2;
	buffer[i] = 0;
	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (value == 0)
		buffer[--i] = '0';
	else
	{
		while (value)
		{
			buffer[--i] = hex_digits[value & 15];
			value >>= 4;
		}
	}
	return (write_str(buffer + i));
}

/*Size of buffer: large enough to hold largest possible hexadecimal
representation of unsigned long long. *2 because sizeof gives the number of
bytes, and 1 byte (octet) = 2 hexa digits. +1 for null terminator.
while loop: start at the end of buffer, perform a bitwise AND operation with
15 (= 0xf = 1111). This will only keep the last 4 bits of value.
Since 4 bits = 1 hexadecimal digit, this will get the corresonding hex value
in hex_digits string.
Then, >>= shifts the value 4 bits to the right to
read the next hex digit.*/