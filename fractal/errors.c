/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:01:50 by maakhan           #+#    #+#             */
/*   Updated: 2024/08/31 12:47:22 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	space_only(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	check_complex(const char *str)
{
	int	flag;
	int	i;

	i = 0;
	flag = 1;
	while (space_only(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (space_only(str[i]))
		i++;
	if (!(str[i] > '0' && str[i] < '9') && str[i] != '\0')
		flag = 0;
	return (flag);
}

int	fractal_menu(void)
{
	int	fd;

	fd = 1;
	ft_putstr_fd("For Mandelbrot set, type :\n", fd);
	ft_putstr_fd("\"mandelbrot\"\n", fd);
	ft_putstr_fd("For Julia set, type :\n", fd);
	ft_putstr_fd("\"julia\" OR \"julia\" \"x\" OR \"julia\" \"x\" \"y\"\n", fd);
	return (0);
}

int	check_args(int ac, char **av, t_fractal *fractal)
{
	if (ac == 2)
	{
		if (!ft_strncmp(av[1], "mandelbrot", 11))
			return (mandelbrot(fractal));
		else if (!ft_strncmp(av[1], "julia", 6))
			return (julia("0", "0", fractal));
	}
	else if (ac == 3)
	{
		if (!ft_strncmp(av[1], "julia", 6))
			return (julia(av[2], "0", fractal));
	}
	else if (ac == 4)
		if (!ft_strncmp(av[1], "julia", 6))
			return (julia(av[2], av[3], fractal));
	return (0);
}
