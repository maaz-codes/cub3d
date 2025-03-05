/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcreer <rcreer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:51:34 by rcreer            #+#    #+#             */
/*   Updated: 2024/07/01 15:31:43 by rcreer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = '\0';
		i++;
	}
}
// int main() {
//     char s1[10] = "Hello";
// 	size_t size = sizeof(s1);

// 	printf("before: %s\n",s1);
// 	ft_bzero(s1,size);
// 	printf("after: %s\n",s1);
// }