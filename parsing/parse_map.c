/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:55:41 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/04 17:57:26 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	valid_nsew(char **map, int row, int i)
{
	int	check;

	check = 0;
	if (map[row - 1][i] == '1' || map[row - 1][i] == '0' ||
		check_direction(map[row - 1][i]))
		check++;
	if (map[row + 1][i] == '1' || map[row + 1][i] == '0' ||
		check_direction(map[row + 1][i]))
		check++;
	if (map[row][i + 1] == '1' || map[row][i + 1] == '0' ||
		check_direction(map[row][i + 1]))
		check++;
	if (map[row][i - 1] == '1' || map[row][i - 1] == '0' ||
		check_direction(map[row][i - 1]))
		check++;
	if (check == 4)
		return (1);
	printf("Not Enclosed Properly\n");
	return (0);
}

int	player_zero_check(char **map, int row, int i)
{
	if (i == 0 || map[row][i + 1] == '\0' || i > ft_strlen(map[row - 1]) ||
		i > ft_strlen(map[row + 1]))
	{
		printf("Not Enclosed Properly\n");
		return (0);
	}
	if (map[row][i + 1] == ' ' || map[row][i - 1] == ' ')
	{
		printf("Not Enclosed Properly\n");
		return (0);
	}
	if (valid_nsew(map, row, i))
		return (1);
	return (0);
}

int	one_check(char **map, int row, int i)
{
	if (map[row][i] == '1')
	{
		if (only_spaces(map[row - 1]) || only_spaces(map[row + 1]))
			return (0);
		return (1);
	}
	return (1);
}

int	pass_through(char **map, int *i, int row, t_parsing *parse)
{	
	if (row == last_row(parse))
		return (1);
	while (map[row][*i] == ' ')
		(*i) += 1;
	if (check_which_texture(map[row], *i) == 7)
	{
		if (!checkpoint(map, row, *i))
			return (0);
		return (2);
	}
	else
		return (0);
}

int	parse_map(t_parsing *parse)
{
	int		i;
	int		row;
	char	**map;

	map = parse->map;
	row = 0;

	if(!check_top_down(map, last_row(parse)))
		return (0);
	if(!check_bottom(parse))
		return (0);
	if(!one_player(parse))
		return (0);
	// if (!check_top_down(map, last_row(parse)) || !check_bottom(parse)
	// 	|| !one_player(parse)) 
	// {
	// 	printf("go here\n");
	// 	return (0);
	// }
	while (++row < parse->map_length)
	{
		i = -1;
		while (map[row][++i])
		{	
			if (pass_through(map, &i, row, parse) == 0)
				return (0);
			else if (pass_through(map, &i, row, parse) == 1)
				return (1);
			else if (pass_through(map, &i, row, parse) == 2)
				break;
		}
	}
	return (1);
}
