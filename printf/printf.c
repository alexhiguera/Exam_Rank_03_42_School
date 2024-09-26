/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:36 by alex              #+#    #+#             */
/*   Updated: 2024/09/24 17:13:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	write_xd(void *ptr, size_t len, int *r)
{
	ssize_t	ret;

	if (*r == -1)
		return ;
	ret = write(1, ptr, len);
	if (ret == -1)
		*r = -1;
	else
		*r += ret;
}

void	put_str(char *str, int *r)
{
	size_t	len;

	if (str == NULL)
		str = "(null)";
	len = 0;
	while (str[len] != '\0')
		len++;
	write_xd(str, len, r);
}

void	put_nbr(int n, int *r)
{
	if (n < 0)
	{
		write_xd("-", 1, r);
		if (n <= -10)
			put_nbr(-(n / 10), r);
		write_xd(&("0123456789"[-(n % 10)]), 1, r);
	}
	else
	{
		if (n >= 10)
			put_nbr(n / 10, r);
		write_xd(&("0123456789"[n % 10]), 1, r);
	}
}

void	put_hex(unsigned int x, int *r)
{
	if (x >= 16)
		put_hex(x / 16, r);
	write_xd(&("0123456789abcdef"[x % 16]), 1, r);
}

void	write_text(char *str, size_t *i, int *r)
{
	size_t	len;

	len = 0;
	while (str[*i + len] != '\0' && str[*i + len] != '%')
		len++;
	write_xd(str + *i, len, r);
	*i += len;
}

void	write_format(char *str, size_t *i, int *r, va_list args)
{
	*i += 1;
	if (str[*i] == 's')
		put_str(va_arg(args, char *), r);
	else if (str[*i] == 'd')
		put_nbr(va_arg(args, int), r);
	else if (str[*i] == 'x')
		put_hex(va_arg(args, unsigned int), r);
	if (str[*i] != '\0')
		*i += 1;
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		r;

	va_start(args, str);
	i = 0;
	r = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			write_text((char *)str, &i, &r);
		else
			write_format((char *)str, &i, &r, args);
	}
	va_end(args);
	return (r);
}

/* int main()
{
	ft_printf("%d\n", ft_printf(""));
	ft_printf("%d\n", ft_printf("HOLA %s\n", NULL));
	ft_printf("%d\n", ft_printf("%d + %d = %d\n", 3, 9, -2147483648));
	ft_printf("%d\n", ft_printf("ME VAS A %s LOS %x\n", "COMER", 0x51af));
} */