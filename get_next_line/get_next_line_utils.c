/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:48:12 by rcreer            #+#    #+#             */
/*   Updated: 2024/07/18 16:48:50 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "../cub3d.h"

int	found_newline(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	len;

	if (!list)
		return ;
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[len++] = '\n';
				str[len] = '\0';
				return ;
			}
			str[len++] = list->content[i++];
		}
		list = list->next;
	}
	str[len] = '\0';
}

int	lentillnewline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*node;

	if (!lst || !*lst)
		return ;
	if (*lst)
	{
		while (*lst)
		{
			node = (*lst)->next;
			free((*lst)->content);
			free(*lst);
			*lst = node;
		}
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
