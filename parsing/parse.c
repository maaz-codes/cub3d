/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:53:00 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/10 17:26:47 by maakhan          ###   ########.fr       */
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
	{
		printf("Invalid Map\n");
		return (0);
	}
	if (!check_parsing(parse, &texture_count, &rgb_count))
		return (0);
	if (is_valid(parse) && texture_count + rgb_count == 6)
		return (1);
	else
	{
		printf("Invalid Values\n");
		return (0);
	}
}

int	parse_init_save(t_parsing **parse, char **av)
{
	if (!init_parse_struct(parse, av))
		return (0);
	if (!check_parse(*parse, av[1]))
		return (0);
	if(!save_texture(*parse, file_open(av[1])))
	{	
		printf("Error texture\n");
		return (0);
	}
	if (!rgb_save(*parse))
	{	
		printf("Invalid RGB\n");
		return (0);
	}
	// if(!valid_xpm_file(*parse))
	// 	return (0);
	print_info(*parse, av);
    get_player_modif_map(*parse);
	return (1);
}

int valid_xpm_file(t_parsing *parse)
{   
    int row;
    int i;
    char **textures;

    row = -1;
    textures = parse->textures;
    while(++row < 4)
    {
        i = -1;
        while(textures[row][++i] != '.' 
            && textures[row][i]);
        if(i == ft_strlen(textures[row]))
        {   
            printf("Not a .xpm file\n");
            return (0);
        }
        else
        {   
            if(ft_strncmp(textures[row] + i,".xpm",3))
                return (printf("Not a .xpm file\n"),0);
        }
    }
    return (1);
}
