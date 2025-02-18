/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 09:02:01 by maakhan           #+#    #+#             */
/*   Updated: 2024/08/31 12:48:56 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static double	ft_pow(int base, unsigned int pow)
{
	double	res;

	res = 1;
	while (pow != 0)
	{
		res = res * base;
		pow--;
	}
	return (res);
}

double	ft_atof(const char *str)
{
	double			res;
	double			sign;
	unsigned int	i;
	unsigned int	j;

	res = 0;
	i = 0;
	sign = 1.0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1.0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (str[i] == '.' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	j = 1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res + (str[i++] - '0') / ft_pow(10.0, j++);
	return (res * sign);
}
