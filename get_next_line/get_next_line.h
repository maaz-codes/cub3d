/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:49:00 by rcreer            #+#    #+#             */
/*   Updated: 2024/07/18 17:19:15 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
t_list				*ft_lstlast(t_list *lst);
void				ft_append(t_list **list, char *buf);
int					lentillnewline(t_list *list);
int					found_newline(t_list *list);
void				copy_str(t_list *list, char *str);
void				clean_node(t_list **list, int len, int i);
char				*get_theline(t_list *list);
void				ft_lstclear(t_list **lst);
#endif