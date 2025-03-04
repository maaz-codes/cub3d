/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:07:26 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/04 18:09:25 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_which_texture(char *file_check, int i)
{
	if ((file_check[i] == 'N' && file_check[i + 1] == 'O'))
		return (1);
	else if ((file_check[i] == 'S' && file_check[i + 1] == 'O'))
		return (2);
	else if ((file_check[i] == 'W' && file_check[i + 1] == 'E'))
		return (3);
	else if ((file_check[i] == 'E' && file_check[i + 1] == 'A'))
		return (4);
	else if (file_check[i] == 'F' && file_check[i + 1] == ' ')
		return (5);
	else if (file_check[i] == 'C' && file_check[i + 1] == ' ')
		return (6);
	else if ((file_check[i] == '1' && file_check[i + 1] == '0')
		|| (file_check[i] == '1' && file_check[i + 1] == '1')
		|| (file_check[i] == '1' && file_check[i + 1] == 'N')
		|| (file_check[i] == '1' && file_check[i + 1] == 'S')
		|| (file_check[i] == '1' && file_check[i + 1] == 'E')
		|| (file_check[i] == '1' && file_check[i + 1] == 'W')
		|| (file_check[i] == '1' && file_check[i + 1] == ' '))
		return (7);
	else
		return (0);
}

int	main_check(char **file_data, int row, int i, t_parsing *parse)
{
	if (check_which_texture(file_data[row], i)
		&& check_which_texture(file_data[row], i) != 0)
	{
		if (check_which_texture(file_data[row], i) < 5)
			check_valid_values(file_data[row], i, parse, "texture");
		return (1);
	}
	return (0);
}

int	appending(char **file_data, int row, int *i, int *valid)
{
	if (check_which_texture(file_data[row], *i) < 5)
	{
		(*i) += 2;
		if (file_data[row][*i] != ' ')
			return (0);
		while (file_data[row][*i] == ' ' && file_data[row][*i])
			(*i) += 1;
		if (*i != ft_strlen(file_data[row]) - 1)
			(*valid) += 1;
		else
			return (0);
		return (1);
	}
	else if (check_which_texture(file_data[row], *i) >= 5
		&& check_which_texture(file_data[row], *i) <= 7)
		return (1);
	return (0);
}

int	check_txt(t_parsing *parse, int *valid, int row, int i)
{
	char	**file_data;

	file_data = parse->file_data;
	while (++row < parse->row)
	{
		i = -1;
		while (++i < ft_strlen(file_data[row]))
		{
			while (file_data[row][i] == ' ')
				i++;
			if (main_check(file_data, row, i, parse))
			{
				if (!appending(file_data, row, &i, &(*valid)))
					return (0);
				break ;
			}
			else if (file_data[row][i] == '\n')
				break ;
			else
				return (0);
		}
	}
	return (1);
}
