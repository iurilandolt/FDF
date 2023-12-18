/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:58:12 by rlandolt          #+#    #+#             */
/*   Updated: 2023/12/18 16:43:23 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
	# define GET_NEXT_LINE_H
#endif

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE	10
#endif

typedef struct s_list
{
	char			*buffer;
	struct	s_list	*next;

}	t_list;
