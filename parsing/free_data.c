/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:02:12 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/06 18:15:04 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_double(char **str, int size)
{
	int	i;

	i = -1;
	while (++i < size && str[i] != NULL)
		free(str[i]);
	free(str);
}

void	free_int(int **num, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(num[i]);
	free(num);
}

void	free_data(t_parsing *parse)
{
	if (parse->check_valid)
		free_int(parse->check_valid, 6);
	if (parse->textures)
	{
		if (!parse->textures[0])
			free(parse->textures);
		else
			free_double(parse->textures, 4);
	}
	if (parse->rgb)
		free_int(parse->rgb, 2);
	if (parse->file_data)
		free_double(parse->file_data, parse->row);
	if (parse->map)
		free_double(parse->map, parse->map_length);
	if (parse)
		free(parse);
}

int	valid_cub_file(char *file_name)
{
	int		i;
	char	buffer[1];
	int		file_check;

	i = -1;
	file_check = file_open(file_name);
	if (!file_check)
		return (close(file_check), 0);
	close(file_check);
	while (file_name[++i] != '.' && file_name[i])
		;
	if (i == ft_strlen(file_name))
		return (0);
	else
	{
		if (!ft_strncmp(file_name + i, ".cub", 3))
			return (1);
		else
		{
			printf("Not a .cub file\n");
			return (0);
		}
	}
	return (0);
}
