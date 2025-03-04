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

void	print_validity(int texture, int rgb, t_parsing *parse)
{
	int	check;

	check = -1;
	printf("\ntexture: %d\n", texture);
	printf("rgb: %d\n", rgb);
	while (++check < 6)
		printf("value: %d\n", parse->check_valid[check][0]);
	if (is_valid(parse) && texture + rgb == 6)
		printf("VALUES VALID\n");
	else
		printf("VALUES ERROR\n");
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
