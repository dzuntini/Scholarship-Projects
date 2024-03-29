/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:12:08 by dzuntini          #+#    #+#             */
/*   Updated: 2021/08/22 22:09:34 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					i;

	d = dst;
	s = src;
	c = (unsigned char)c;
	i = -1;
	while (n - ++i)
	{
		*(d + i) = *(s + i);
		if (*(s + i) == c)
			return ((void *)(d + 1 + i));
	}
	return (0);
}
