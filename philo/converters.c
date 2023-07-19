/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:50:17 by asepulve          #+#    #+#             */
/*   Updated: 2023/07/19 23:03:39 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		count++;
	}
	return ((void *) dest);
}

int	ft_atoi(const char *nptr)
{
	int	count;
	int	number;
	int	sign;

	number = 0;
	count = 0;
	sign = 1;
	while ((nptr[count] == 32) || ((nptr[count] >= 9) && (nptr[count] <= 13)))
		count++;
	if ((nptr[count] == '+') || (nptr[count] == '-'))
	{
		if ((nptr[count] == '-'))
			sign = -1;
		count++;
	}
	while (nptr[count] >= '0' && nptr[count] <= '9')
	{
		number = (number * 10) + nptr[count] - 48;
		count++;
	}
	return (number * sign);
}


static size_t	getlength(int n)
{
	size_t	length;

	length = 1;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static char	*convert(char *str, size_t sign, int n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 1;
	while (i++ < getlength(n) - 1)
		len = len * 10;
	i = 0;
	if (sign)
		str[i++] = '-';
	while (len > 0)
	{
		str[i++] = n / (len) + 48;
		n = n % (len);
		len = len / 10;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	sign;
	char	*str;

	if (n == -2147483648)
	{
		str = (char *)malloc(12);
		if (!str)
			return (NULL);
		return (ft_memcpy(str, "-2147483648\0", 12));
	}
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = n * (-1);
	}
	str = (char *)malloc(getlength(n) + sign + 1);
	if (!str)
		return (NULL);
	return (convert(str, sign, n));
}
