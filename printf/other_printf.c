/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:09:51 by alex              #+#    #+#             */
/*   Updated: 2024/09/24 17:41:24 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void ft_put_str(char *str, int *size)
{
	if(!str)
		str = "(null)";
	while(*str)
		*size += write(1, str++, 1);
}

void ft_put_digit(long long int nbr, int base, int *size)
{
	if(nbr < 0)
	{
		nbr *= -1;
		*size += write(1, "-",1);
	}
	if(nbr >= base)
		ft_put_digit((nbr / base), base, size);
	*size += write(1, &("0123456789abcdef"[nbr % base]),1);
}

int ft_printf(const char *format, ... )
{
	int size = 0;
	va_list ptr;
	va_start(ptr, format);
	while (*format)
	{
		if ((*format == '%') && (((*(format + 1) == 's') \
			|| (*(format + 1) == 'd') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				ft_put_str(va_arg(ptr, char *), &size);
			else if (*format == 'd')
				ft_put_digit((long long int)va_arg(ptr, int), 10, &size);
			else if (*format == 'x')
				ft_put_digit((long long int)va_arg(ptr, unsigned int), 16, &size);
		}
		else
			size += write(1, format, 1);
		format++;
	}
	return (va_end(ptr), size);
}
