/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:09:42 by dzuntini          #+#    #+#             */
/*   Updated: 2021/01/19 15:16:33 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	unsigned int idst;
	unsigned int lsrc;

	idst = 0;
	while (dst[idst] != '\0')
		idst++;
	lsrc = 0;
	while (lsrc + idst + 1 < dstsize && src[lsrc] != '\0')
	{
		dst[idst + lsrc] = src[lsrc];
		lsrc++;
	}
	dst[idst + lsrc] = '\0';
	lsrc = 0;
	while (src[lsrc] != '\0')
		lsrc++;
	if (dstsize == 0)
		return (lsrc);
	if (idst < dstsize)
		return (idst + lsrc);
	else
		return (dstsize + lsrc);
}
