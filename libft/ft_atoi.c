/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maakhan <maakhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:01:48 by rcreer            #+#    #+#             */
/*   Updated: 2025/03/10 19:49:07 by maakhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_atoi(const char *nptr)
{
	unsigned long long	c;
	int					conv;

	conv = 1;
	c = 0;
	while (*nptr == 32 || (*nptr <= 13 && *nptr >= 9))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			conv *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		c = c * 10 + *nptr - '0';
		if (c > LLONG_MAX && conv == -1)
			return (-1);
		if (c > LLONG_MAX)
			return (-1);
		nptr++;
	}
	return (c * conv);
}

// int main(void)
// {
// 	char *t1 = "48";
// 	printf("%d\n",ft_atoi(t1));
// 	printf("%d\n",atoi(t1));
// }