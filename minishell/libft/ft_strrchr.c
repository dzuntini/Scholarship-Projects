/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:30:24 by dzuntini          #+#    #+#             */
/*   Updated: 2021/08/22 22:12:23 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;
	int	cpt;

	cpt = -1;
	len = ft_strlen(s);
	while (++cpt <= len)
		if (*(s + len - cpt) == c)
			return ((char *)(s + len - cpt));
	return (0);
}
