/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:33:58 by alejarod          #+#    #+#             */
/*   Updated: 2023/07/02 12:22:05 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// man va_arg
#include <stdarg.h>
#include <unistd.h>

#include <stdio.h>

int	ft_putstr(char *str)
{
	int i = 0;
	// don't forget the special case
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int ft_putnbr(int n)
{
	// man integer working in MACOS???
	if (n = INT_MIN)
}

int	ft_puthex()
{
	
} */

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
		len += ft_puthex();
	} */
	return (len);
}





/* 
step 1. declare, start and end the va_list
step 2. loop the string until we find a %

remember:
declare: va_list <list_name>;
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
		else		// else if !!!!
			len = ft_format(str[++i], len, args); // need ++i to skip the char of the variable and not write it
		i++;
	}
	va_end(args);
	return (len);
}

int	main(void)
{
	char *str = "Alex";
	int or_bytes;
	int	my_bytes;

	// write exactly the same string, only vary the bytes to check result
	my_bytes = ft_printf("result is |||%s|||\n", str);	
	or_bytes = printf("result is |||%s|||\n", str);
	
	printf("my bytes are: %d\n", my_bytes);
	printf("or bytes are: %d\n", or_bytes);
	return (0);
}