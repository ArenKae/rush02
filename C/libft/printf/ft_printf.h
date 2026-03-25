/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:58:00 by acosi             #+#    #+#             */
/*   Updated: 2023/02/03 09:15:19 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>	// Needed for uintptr_t

int		ft_printf(const char *str, ...);
int		ft_format(va_list args, const char *str);
int		write_char(int c);
int		write_str(char *str);
void	ft_putstr(char *str);
int		write_percent(void);
int		write_nbr(int value);
int		write_uint(unsigned int value);
int		write_ptr(uintptr_t p);
int		write_hex(unsigned int value, int uppercase);

#endif