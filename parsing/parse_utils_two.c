/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:55:06 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/04 17:55:32 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	print_validity(int texture, int rgb, t_parsing *parse)
// {
// 	int	check;

// 	check = -1;
// 	printf("\ntexture: %d\n", texture);
// 	printf("rgb: %d\n", rgb);
// 	while (++check < 6)
// 		printf("value: %d\n", parse->check_valid[check][0]);
// 	if (is_valid(parse) && texture + rgb == 6)
// 		printf("VALUES VALID\n");
// 	else
// 		printf("VALUES ERROR\n");
// }

void	get_xy_val(t_parsing *parse)
{
	int y;
	int x;

	y = -1;
	while(++y < parse->map_length)
	{
		x = -1;
		while(parse->map[y][++x] != '\n' && parse->map[y][x])
		{
			if(parse->map[y][x] == 'W' || parse->map[y][x] == 'E'
			|| parse->map[y][x] == 'N' || parse->map[y][x] == 'S')
			{
				parse->x_pos = x;
				parse->y_pos = y;
				break;
			}
		}
	}
	printf("x_val: %d\n",parse->x_pos);
	printf("y_val: %d\n",parse->y_pos);
}

void	modif_map(t_parsing *parse)
{
	int y;
	int x;

	y = -1;
	while(++y < parse->map_length)
	{	
		x = -1;
		while(parse->map[y][++x] != '\n' && parse->map[y][x])
		{
			if(parse->map[y][x] == 'W' || parse->map[y][x] == 'E'
			|| parse->map[y][x] == 'N' || parse->map[y][x] == 'S')
			{
				parse->map[y][x] = '0';
				break;
			}
		}
	}
	printf("\nnew map\n");
	for(int f = 0; f < parse->map_length; f++)
		printf("%s",parse->map[f]);
	printf("\n");
}
void	get_player_modif_map(t_parsing *parse)
{
	int y;
	int x;

	y = -1;
	while(++y < parse->map_length)
	{	
		x = -1;
		while(parse->map[y][++x] != '\n' && parse->map[y][x])
		{
			if(parse->map[y][x] == 'W' || parse->map[y][x] == 'E'
			|| parse->map[y][x] == 'N' || parse->map[y][x] == 'S')
			{
				parse->player = parse->map[y][x];
				break;
			}
		}
	}
	printf("\nplayer : %c\n",parse->player);
	get_xy_val(parse);
	modif_map(parse);
}

void	print_rgb_map(t_parsing *parse)
{
	int	i;

	printf("F ");
	i = -1;
	while (++i < 3)
	{
		if (i == 2)
			printf("%d\n", parse->rgb[0][i]);
		else
			printf("%d,", parse->rgb[0][i]);
	}
	printf("\n");
	printf("C ");
	i = -1;
	while (++i < 3)
	{
		if (i == 2)
			printf("%d\n", parse->rgb[1][i]);
		else
			printf("%d,", parse->rgb[1][i]);
	}
	printf("\n");
	i = -1;
	while (++i < parse->map_length)
		printf("%s", parse->map[i]);
}
