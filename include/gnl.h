/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:58:12 by rlandolt          #+#    #+#             */
/*   Updated: 2024/01/10 12:34:50 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H

# define GNL_H

# define BUFFER_SIZE	10

typedef struct s_list
{
	char			*buffer;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*get_line(t_list *lst);
int		has_newline(t_list *lst);
int		line_len(t_list *lst);
t_list	*get_last(t_list *lst);
void	append_string(t_list *lst, char *str);

#endif
