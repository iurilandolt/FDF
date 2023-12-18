/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:58:18 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/18 21:23:27 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/gnl.h"

static void	append_list(t_list **lst, char *buffer)
{
	t_list	*new;
	t_list	*last;

	last = get_last(*lst);
	new = (t_list *)malloc(sizeof(t_list));
	if(!new)
		return ;
	if (!last)
		*lst = new;
	else
		last->next = new;
	new->buffer = buffer;
	new->next = NULL;
}

static void	cleanup(t_list **lst, t_list *new, char *buffer)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->buffer);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (new->buffer[0])
		*lst = new;
	else
	{
		free(buffer);
		free(new);
	}
}

static void	mantain_list(t_list **lst)
{
	t_list	*new;
	t_list	*last;
	int	i;
	int	j;
	char *buffer;

	if(!lst)
		return ;
	new = (t_list *)malloc(sizeof(t_list));
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!new || !buffer)
		return ;
	last = get_last(*lst);
	i = 0;
	j = 0;
	while (last->buffer[i] && last->buffer[i] != '\n')
		i++;
	while (last->buffer[i] && last->buffer[++i])
		buffer[j++] = last->buffer[i];
	buffer[j] = '\0';
	new->buffer = buffer;
	new->next = NULL;
	cleanup(lst, new, buffer);
}

static void	init_list(t_list **lst, int fd)
{
	int c_read;
	char *buffer;

	while (!has_newline(*lst))
	{
		buffer = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
		if (!buffer)
			return ;
		c_read = read(fd, buffer, BUFFER_SIZE);
		if (!c_read)
		{
			free(buffer);
			return ;
		}
		buffer[c_read] = '\0';
		append_list(lst, buffer);
	}
}

char	*get_next_line(int fd)
{
	static	t_list *lst;
	char	*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	init_list(&lst, fd);
	if (!lst)
		return (NULL);
	next_line = get_line(lst);
	mantain_list(&lst);
	return (next_line);
}

/*
int	open_file(char *argv, int *filein)
{
	if ((*filein = open(argv, O_RDONLY)) <= 0)
		return (-1);
	return (*filein);
}

int	main(int argc, char **argv)
{
	int filein;
	char *line;

	if (argc == 2)
	{
		if (open_file(argv[1], &filein) > 0)
		{
			while ((line = get_next_line(filein)))
			{
				printf("%s", line);
				free(line);
			}
		}

	}
	close(filein);
	return(0);
}
*/
