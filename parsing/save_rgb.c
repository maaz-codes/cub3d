/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:04:31 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/10 19:51:08 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	skipper_val(char *remove_space)
{
	int	skipper;

	skipper = 0;
	if (!ft_strncmp(remove_space, "F", 1) || !ft_strncmp(remove_space, "C", 1))
	{
		while (!(remove_space[skipper] >= '0' && remove_space[skipper] <= '9'))
			skipper++;
	}
	return (skipper);
}

int	valid_num(int number)
{
	if (number < 0 || number > 255)
		return (0);
	return (1);
}

int	set_values_rgb(char *file_check, t_parsing *parse, char *pos, int rgb_pos)
{
	char	**remove_comma;
	char	*remove_space;
	char	*trim_pos;
	int		rgb_num;
	int		i;

	i = -1;
	trim_pos = ft_strtrim(file_check, pos);
	remove_comma = ft_split(trim_pos, ',');
	free(trim_pos);
	while (++i < 3 && remove_comma[i] != NULL)
	{
		remove_space = ft_strtrim(remove_comma[i], " ");
		rgb_num = ft_atoi(remove_space + skipper_val(remove_space));
		if (!ft_strncmp(remove_space, "\n", 1) || !valid_num(rgb_num))
		{
			(free(remove_space), free_double(remove_comma, 3));
			return (0);
		}
		free(remove_space);
		parse->rgb[rgb_pos][i] = rgb_num;
	}
	free_double(remove_comma, 3);
	return (1);
}

int	rgb_save(t_parsing *parse)
{
	char	**file_check;
	int		i;
	int		row;

	row = -1;
	file_check = parse->file_data;
	while (++row < parse->row)
	{
		i = 0;
		while (file_check[row][i])
		{
			if (check_which_texture(file_check[row], i) == 5)
				if (!set_values_rgb(file_check[row], parse, "F", 0))
					return (0);
			if (check_which_texture(file_check[row], i) == 6)
				if (!set_values_rgb(file_check[row], parse, "C", 1))
					return (0);
			i++;
		}
	}
	return (1);
}
