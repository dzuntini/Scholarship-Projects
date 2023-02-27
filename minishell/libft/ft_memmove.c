/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:21:49 by dzuntini          #+#    #+#             */
/*   Updated: 2021/01/20 08:10:14 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*lastd;
	const char	*lasts;

	d = dst;
	s = src;
	if (!dst && !src)
	{
		return (0);
	}
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		lastd = d + (len - 1);
		lasts = s + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
