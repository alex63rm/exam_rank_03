/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejarod <alejarod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 21:33:58 by alejarod          #+#    #+#             */
/*   Updated: 2023/07/01 22:44:27 by alejarod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// man va_arg
#include<stdarg.h>


int	ft_putstr()
{
	
}

int ft_putnbr()
{
	
}

int	ft_puthex()
{
	
}

int	ft_format(char c, int len, va_list args)
{
	if (c == 's')
	{
		len += ft_putstr();
	}
	if (c == 'd')
	{
		len += ft_putnbr();
	}
	if (c == 'x')
	{
		len += ft_puthex();
	}
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
	va_list	args;	// declare a variable list of arguments
	int		len;	// the bytes that will be printed by ft_printf
	int		i;

	va_start(args, str);	// start the first argument of the list (the string)

	len = 0;
	i = 0;
	while (str[i])
	{
		if(str[i] != '%')	// loop and write if we don't find a %, adding length to the return
		{
			write(1, &str[i], 1);
			len++;
		}
		else		// else if !!!!
			len = ft_format(str[i+1], len, args); 
		i++;
	}
	va_end(args);
	return (len);
}