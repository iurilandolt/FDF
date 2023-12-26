/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:03:02 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/26 13:52:55 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

size_t	ft_strlen(const char *s)
{
	size_t	pos;

	pos = 0;
	while (*s++)
		pos++;
	return (pos);
}

int	tab_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int ft_atoi(char *str)
{
	int n;
	int sign;

	n = 0;
	sign = 1;
	while(*str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if(*str++ == '-')
			sign = -1;
	while(*str >= '0' && *str <= '9')
		n = n * 10 + (*str++ - '0');
	return (n * sign);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (*(src + i) && size && i < size - 1)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	if (size - i != 0)
		*(dest + i) = '\0';
	return (ft_strlen(src));
}
