/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:00:33 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/08 16:23:09 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"

t_list	*get_last(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	has_newline(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->buffer[i] && i < BUFFER_SIZE)
		{
			if (lst->buffer[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

int	line_len(t_list *lst)
{
	int	i;
	int	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->buffer[i])
		{
			if (lst->buffer[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

char	*get_line(t_list *lst)
{
	int		len;
	char	*line;

	if (!lst)
		return (NULL);
	len = line_len(lst);
	line = (char *)malloc(len * sizeof(char) + 1);
	if (!line)
		return (NULL);
	append_string(lst, line);
	return (line);
}

void	append_string(t_list *lst, char *str)
{
	int	i;
	int	j;

	if (!lst)
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->buffer[i])
		{
			if (lst->buffer[i] == '\n')
			{
				str[j] = '\n';
				str[j + 1] = '\0';
				return ;
			}
			str[j] = lst->buffer[i];
			i++;
			j++;
		}
		lst = lst->next;
	}
	str[j] = '\0';
}
