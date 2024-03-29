/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:02:55 by dzuntini          #+#    #+#             */
/*   Updated: 2021/01/23 17:17:17 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr;
	const char	*s;

	ptr = dst;
	s = src;
	if (dst == 0 && src == 0)
	{
		return (0);
	}
	while (n--)
		*ptr++ = *s++;
	return (dst);
}
