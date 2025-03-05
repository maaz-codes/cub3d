/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:02:39 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/04 18:04:17 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	last_rgb(char *file_check, int *i, int *rgb_check)
{
	(*i) += 1;
	while (file_check[*i] == ' ' && file_check[*i])
		(*i) += 1;
	if (!file_check[(*i)])
		return (0);
	while (file_check[*i])
	{
		if (file_check[(*i)] >= '0' && file_check[(*i)] <= '9')
		{
			(*i) += 1;
			continue ;
		}
		else
			break ;
	}
	while (file_check[(*i)] == ' ' && file_check[(*i)])
		(*i) += 1;
	if (file_check[(*i)] == '\n')
	{
		(*rgb_check) += 1;
		return (1);
	}
	else
		return (0);
}

int	one_and_two_rgb(char *file_check, int *i, int *rgb_check)
{
	while (file_check[*i])
	{
		if (file_check[*i] >= '0' && file_check[*i] <= '9')
		{
			(*i) += 1;
			continue ;
		}
		else
			break ;
	}
	while (file_check[(*i)] == ' ' && file_check[(*i)])
		(*i) += 1;
	if ((file_check[(*i)] == ',' && (file_check[(*i) + 1] == ' '))
		|| file_check[(*i)] == ',' || ((file_check[(*i)] >= '0'
				&& file_check[(*i)] <= '9') && file_check[*i - 1] != ' '))
	{
		(*rgb_check) += 1;
		return (1);
	}
	else
		return (0);
}

int	rgb_loop(char *file_check, int *i, int *rgb_check, int *valid)
{
	while (file_check[*i])
	{
		if ((*rgb_check) == 2)
		{
			if (!last_rgb(file_check, &(*i), &(*rgb_check)))
				break ;
		}
		else if (file_check[(*i)] == ' ')
			(*i) += 1;
		else if (file_check[(*i)] >= '0' && file_check[(*i)] <= '9')
		{
			if (!one_and_two_rgb(file_check, &(*i), &(*rgb_check)))
				break ;
		}
		else
			break ;
		(*i) += 1;
	}
	if ((*rgb_check) == 3)
		(*valid) += 1;
	else
		return (0);
	return (1);
}

int	rgb_check(t_parsing *parse, int *valid)
{
	int		i;
	int		row;
	char	**file_check;
	int		rgb_check;

	row = -1;
	file_check = parse->file_data;
	while (++row < parse->row)
	{
		i = -1;
		while (++i < ft_strlen(file_check[row]))
		{
			rgb_check = 0;
			if (file_check[row][i] == 'F' || file_check[row][i] == 'C')
			{
				check_valid_values(file_check[row], i, parse, "rgb");
				i += 1;
				if (!rgb_loop(file_check[row], &i, &rgb_check, &(*valid)))
					return (0);
			}
		}
	}
	return (1);
}
