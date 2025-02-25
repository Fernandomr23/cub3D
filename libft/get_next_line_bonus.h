/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:43:06 by fmorenil          #+#    #+#             */
/*   Updated: 2024/06/27 10:52:03 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*ft_lstlast(t_list *lst);
int		ft_newline(t_list *list);
void	generate_line(t_list *list, char *next_line);
int		ft_strlen_to_nl(t_list *list);
void	free_list(t_list **list, t_list *clean_node, char *buf);

#endif
