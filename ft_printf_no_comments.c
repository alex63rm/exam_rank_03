/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:34:24 by alejarod          #+#    #+#             */
/*   Updated: 2023/07/04 17:13:27 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdarg.h>
#include<limits.h>

//#include<stdio.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int i = 0;
	
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_intlen(int nbr)
{
	int digits = 1;

	while (nbr >= 10)
	{
		nbr = nbr / 10;
		digits++;
	}
	return (digits);
}

int	ft_putnbr(int n)
{
	int len_nbr = 0;
	
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		len_nbr++;
		n = n * -1;
	}
	len_nbr += ft_intlen(n);
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + 48);
	return (len_nbr);
}

int	ft_un_intlen(unsigned int hex)
{
	int digits = 1;

	while (hex >= 16)
	{
		hex = hex / 16;
		digits++; 
	}
	return (digits);
}

int	ft_puthex(unsigned int hex)
{
	int len_hex = 0;

	len_hex += ft_un_intlen(hex);
	if (hex >= 16)
		ft_puthex(hex / 16);
	ft_putchar("0123456789abcdef"[hex % 16]);
	return (len_hex);
}

int	ft_check_format(char c, va_list args, int len)
{
	if (c == 's')
		len += ft_putstr(va_arg(args, char *));
 	if (c == 'd')
		len += ft_putnbr(va_arg(args, int));
	if (c == 'x')
		len += ft_puthex(va_arg(args, unsigned int));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int	len = 0;
	int	i = 0;
	va_list	args;

	va_start(args, str);
	
	while (str[i])
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			len++;
		}
		else
			len = ft_check_format(str[++i], args, len);
	i++;
	}
	
	va_end(args);

	return (len);
}

/* int	main(void)
{
	char			*str = "(null)hello";
	int				num = -2147483648;
	unsigned int	hex = 0x7fffffff;

	int my_bytes = ft_printf("result is |%s|, |%d|, |%x|\n", str, num, hex);
	int or_bytes =    printf("result is |%s|, |%d|, |%x|\n", str, num, hex);
	
	printf("my: |%d|\n", my_bytes);
	printf("or: |%d|\n", or_bytes);
	return (0);
} */