/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:53:00 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/04 17:54:19 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_info(t_parsing *parse, char **av)
{
	printf("%s %s VALID\n\n", av[0], av[1]);
	printf("NO %s\n", parse->textures[0]);
	printf("SO %s\n", parse->textures[1]);
	printf("WE %s\n", parse->textures[2]);
	printf("EA %s\n", parse->textures[3]);
	printf("\n");
	print_rgb_map(parse);
	printf("\n");
}

int	check_parsing(t_parsing *parse, int *texture_count, int *rgb_count)
{
	if (!parse_map(parse))
	{
		printf("Invalid Map\n");
		return (0);
	}
	if (!check_txt(parse, &(*texture_count), -1, -1))
	{
		printf("Invalid Textures/RGB\n");
		return (0);
	}
	if (!rgb_check(parse, &(*rgb_count)))
	{
		printf("Invalid RGB\n");
		return (0);
	}
	return (1);
}

int	check_parse(t_parsing *parse, char *file)
{
	int	texture_count;
	int	rgb_count;

	texture_count = 0;
	rgb_count = 0;
	get_rows(parse, file_open(file));
	if (!init_file_data(parse))
		return (0);
	get_file_data(parse, file_open(file));
	if (!get_map(parse))
		return (0);
	if (!check_parsing(parse, &texture_count, &rgb_count))
		return (0);
	if (is_valid(parse) && texture_count + rgb_count == 6)
		return (1);
	else
		return (0);
}

int	parse_init_save(char **av)
{
	int			file_check;
	t_parsing	*parse;

	file_check = file_open(av[1]);
	if (!init_parse_struct(&parse) || !file_check)
	{
		close(file_check);
		return (0);
	}
	close(file_check);
	if (!check_parse(parse, av[1]))
	{
		free_data(parse);
		return (0);
	}
	if (!save_texture(parse, file_open(av[1]))
		|| !save_rgb(parse, file_open(av[1])))
	{
		free_data(parse);
		return (0);
	}
	print_info(parse, av);
    get_player_modif_map(parse);
	free_data(parse);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!parse_init_save(av))
			return (1);
	}
	else
		printf("Invalid Args");
	return (0);
}
