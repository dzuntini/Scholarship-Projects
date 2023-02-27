/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:34:08 by dzuntini          #+#    #+#             */
/*   Updated: 2021/01/23 16:15:27 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		cpt;

	if (!dst)
	{
		return ((size_t)ft_strlen(src));
	}
	if (!dstsize)
	{
		return ((size_t)ft_strlen(src));
	}
	cpt = 0;
	while (cpt < (int)dstsize - 1 && src[cpt])
	{
		dst[cpt] = src[cpt];
		cpt++;
	}
	dst[cpt] = '\0';
	return ((size_t)ft_strlen(src));
}
