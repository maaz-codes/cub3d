/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:57:43 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/04 17:59:11 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	checkpoint(char **map, int row, int i)
{	
	while (map[row][i])
	{
		if (map[row][i] == '1' || map[row][i] == ' ')
		{
			if (!one_check(map, row, i))
				return (0);
			i++;
		}
		else
		{
			if (map[row][i] == '\n')
				break ;
			else if (map[row][i] == '0' || check_direction(map[row][i]))
			{
				if (!player_zero_check(map, row, i))
					return (0);
			}
			else
				return (0);
			i++;
		}
	}
	return (1);
}

int	last_row(t_parsing *parse)
{
	int		row;
	int		i;
	char	**map;

	map = parse->map;
	row = parse->map_length - 1;
	while (row >= 0)
	{	
		i = 0;
		while (map[row][i])
		{
			while (map[row][i] == ' ' || map[row][i] == '\t')
				i++;
			if (check_which_texture(map[row], i) == 7)
				return (row);
			else if(map[row][i] == '\n')
				break;
			else
				return (0);
			i++;
		}
		row--;
	}
	return (0);
}

int	 check_top_down(char **map, int last_row)
{
	int	i;

	i = 0;
	if(last_row == 0)
		return (0);
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\n')
			return (0);
		i++;
	}
	i = 0;
	while (map[last_row][i])
	{	
		if (map[last_row][i] != '1' && map[last_row][i] != ' ' && map[last_row][i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_bottom(t_parsing *parse)
{
	int		i;
	int		row;
	char	**map;

	map = parse->map;
	row = -1;
	while (++row < parse->map_length)
	{
		i = -1;
		if (map[row][0] == '\n')
			row++;
		else
		{
			while (++i < ft_strlen(map[row]) && map[row][i] == '\n')
			{
				if (map[row][i] != '1' || map[row][i] != ' ' ||
					map[row][i] != '0' || map[row][i] != 'N'
					|| map[row][i] != 'S' || map[row][i] != 'E'
					|| map[row][i] != 'W' || map[row][i] != '\n')
					return (0);
			}
		}
	}
	return (1);
}

int	one_player(t_parsing *parse)
{
	int		i;
	int		row;
	char	**map;
	int		player;

	player = 0;
	map = parse->map;
	row = -1;
	while (++row < parse->map_length)
	{
		i = -1;
		while (++i < ft_strlen(map[row]) && map[row][i] != '\n')
		{
			if (check_direction(map[row][i]))
				player++;
			if (player > 1)
				return (0);
		}
	}
	if(player == 0)
	{
		printf("No Player\n");
		return (0);
	}
	return (1);
}
