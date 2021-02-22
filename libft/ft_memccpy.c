/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:46:12 by dzuntini          #+#    #+#             */
/*   Updated: 2021/01/20 14:54:53 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if ((t2[i] = t1[i]) == (unsigned char)c)
			return (t2 + ++i);
		i++;
	}
	return (NULL);
}
