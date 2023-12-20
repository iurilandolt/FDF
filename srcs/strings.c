/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:03:02 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/20 14:12:41 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	fdf_strlen(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] != '-')
			++counter;
		++i;
	}
	return(counter);
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
