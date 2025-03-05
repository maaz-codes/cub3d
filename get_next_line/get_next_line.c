/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:49:38 by rcreer            #+#    #+#             */
/*   Updated: 2024/07/18 17:29:58 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "../cub3d.h"

void	clean_node(t_list **list, int len, int i)
{
	t_list	*last_node;
	t_list	*clean_node;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
	last_node = ft_lstlast(*list);
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[i++])
		buf[len++] = last_node->content[i];
	buf[len] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	ft_lstclear(list);
	if (clean_node->content[0])
		*list = clean_node;
	else
	{
		free(clean_node);
		free(buf);
	}
}

char	*get_theline(t_list *list)
{
	int		strlen;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	strlen = lentillnewline(list);
	next_str = malloc(strlen + 1);
	if (!next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	ft_append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

void	list_create(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	char_read = 1;
	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buf);
			free(list);
			return ;
		}
		if (char_read == 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		ft_append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;
	int				len_of_nextline;
	int				loop_through_list;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0
		|| BUFFER_SIZE >= INT_MAX)
	{
		ft_lstclear(&list);
		return (NULL);
	}
	list_create(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_theline(list);
	if (!next_line)
		return (NULL);
	len_of_nextline = 0;
	loop_through_list = 0;
	clean_node (&list, len_of_nextline, loop_through_list);
	return (next_line);
}
