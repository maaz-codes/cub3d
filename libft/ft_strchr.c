/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:56:30 by rcreer            #+#    #+#             */
/*   Updated: 2024/07/01 15:35:45 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

// int main()
// {
// 	char *src = "the cake is a lie !\0I'm hidden lol\r\n";
//  	char *d1 = strchr(src, 'c');
//  	char *d2 = ft_strchr(src, 'c');

//  	printf("%s\n%s\n",d1,d2);
// 	printf("%lu\n",sizeof(src));

// }
