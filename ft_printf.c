/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:33:58 by alejarod          #+#    #+#             */
/*   Updated: 2023/07/04 17:31:10 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// man va_arg
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#include <stdio.h>

// needed for printing hex and num
int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

//compute the number of digits
int	ft_intlen(unsigned int n)
{
	int len = 1;		// start in 1 for 1 digit case
	while (n >= 10)		// loop to count digits!!!
	{
		n = n / 10;
		len++;
	}
	return (len);
}
// same as above but with 16
int	ft_un_intlen(unsigned int hex)
{
	int	len_hex = 1;

	while (hex >= 16)
	{
		hex = hex / 16;
		len_hex++;
	}
	return (len_hex);
}
/*
special case if !str
*/
int	ft_putstr(char *str)
{
	int i = 0;
	// don't forget the special case
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

/*
5 steps:
1. if min_int
2. if negative:
	a. write sign
	b. add 1 to len_nbr
	c. convert to +
3. calculate len of number
4. if >= 10 recursive (recursive no loop!!)
5. Write the digits 1 by 1, with module, converting to char
*/
int ft_putnbr(int n)
{
	int	len_nbr = 0;
	
	// man integer working in MACOS???
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;		// convert to positive to count
		len_nbr++;
	}
	len_nbr += ft_intlen(n);	// count the number of digits
	if (n >= 10)				// recursive no loop!
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + 48);	// one char at a time
	return (len_nbr);
}


// hex is unsigned
int	ft_puthex(unsigned int hex)
{
	int	len_hex = 0;
	
	len_hex += ft_un_intlen(hex);
	if (hex >= 16)		// recursive no loop
		ft_puthex(hex / 16);
	ft_putchar("0123456789abcdef"[hex % 16]);	// this formula
	return (len_hex);	
}


//check the char type and pass it. len+=
int	ft_format(char c, int len, va_list args)
{
	if (c == 's')
	{
		// I am passing as an argument the "char *" type from the list of arguments
		len += ft_putstr(va_arg(args, char *));
	}
	if (c == 'd')
	{
		len += ft_putnbr(va_arg(args, int));
	}
	if (c == 'x')
	{
		len += ft_puthex(va_arg(args, unsigned int));	// hex cannot be negative
	}
	return (len);
}

/* 
step 1. declare, start and end the va_list
step 2. loop the string until we find a %

remember:
declare: 	va_list <list_name>;
ft-start:	va_start(<list_name>, <first_data_type>)
ft-next:	va_arg(<list_name>, <next_data_type>)
ft-end		va_end(<list_name>)

*/
//DUDA SI PUEDO PONER str??? subject dice solamente (const char *, ...)
int	ft_printf(const char *str, ...)
{
	// declare the variable list of arguments
	va_list	args;			// declare a variable list of arguments
	va_start(args, str);	// start the first argument of the list (the string)
	int		len = 0;		// the bytes that will be printed by ft_printf
	int		i = 0;
	
	while (str[i])
	{
		if(str[i] != '%')	// loop and write if we don't find a %, adding length to the return
		{
			write(1, &str[i], 1);
			len++;
		}
		else									  // only len = in this one, the rest is +=
			len = ft_format(str[++i], len, args); // need ++i to skip the char of the variable and not write it
		i++;
	}
	va_end(args);
	return (len);
}

int	main(void)
{
	char *str = "(null)Alex";
	int n = INT_MAX;
	unsigned int hex = 0x7fffffff;
	
	int or_bytes;
	int	my_bytes;

	// write exactly the same string, only vary the bytes to check result
	my_bytes = ft_printf("result is |||%s|||, |||%d|||, |||%x|||\n", str, n, hex);	
	or_bytes =    printf("result is |||%s|||, |||%d|||, |||%x|||\n", str, n, hex);
	
	printf("my bytes are: %d\n", my_bytes);
	printf("or bytes are: %d\n", or_bytes);
	return (0);
}