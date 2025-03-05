/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:59:19 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/04 18:00:34 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_direction(char player)
{
	if (player == 'N' || player == 'S'
		|| player == 'E' || player == 'W')
		return (1);
	else
		return (0);
}

int	only_spaces(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\n')
	{
		if (map[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	get_location(char **file_data)
{
	int	row;
	int	len;

	row = 0;
	while (file_data[row])
	{
		len = 0;
		while (file_data[row][len])
		{
			while (file_data[row][len] == ' ')
				len++;
			if (check_which_texture(file_data[row], len) == 7)
				return (row);
			else
				break;
		}
		row++;
	}
	return (0);
}

int	get_map(t_parsing *parse)
{
	int	i;
	int	map_loc;

	i = 0;
	map_loc = get_location(parse->file_data);
	if(!map_loc)
		return (0);
	parse->map_length = parse->row - map_loc;
	parse->map = malloc((parse->row - map_loc + 1) * sizeof(char **));
	if (!parse->map)
		return (0);
	while (map_loc < parse->row)
	{
		parse->map[i] = ft_calloc(ft_strlen(parse->file_data[map_loc]) + 1,
				sizeof(char));
		if (!parse->map[i])
			return (0);
		ft_strlcpy(parse->map[i], parse->file_data[map_loc],
			ft_strlen(parse->file_data[map_loc]) + 1);
		map_loc++;
		i++;
	}
	printf("\n");
	parse->map[i] = NULL;
	return (1);
}
