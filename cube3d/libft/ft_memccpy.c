/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:46:12 by dzuntini          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:34 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;
	size_t			i;

	t1 = (unsigned char *)src;
	t2 = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		t2[i] = t1[i];
		if (t2[i] == (unsigned char)c)
			return (t2 + ++i);
		i++;
	}
	return (NULL);
}
