/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:05:47 by dzuntini          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:34 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	unsigned int	ft_size;
	unsigned int	j;

	ft_size = ft_strlen(src);
	if (ft_size + 1 < dstsize)
	{
		j = -1;
		while (++j < ft_size + 1)
			dst[j] = src[j];
	}
	else if (dstsize)
	{
		j = -1;
		while (++j < dstsize - 1)
			dst[j] = src[j];
		dst[j] = '\0';
	}
	return (ft_size);
}
