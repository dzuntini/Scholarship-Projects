/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:34:27 by dzuntini          #+#    #+#             */
/*   Updated: 2021/09/25 13:41:14 by pcarella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	len;
	int	cpt;

	cpt = -1;
	len = ft_strlen(s);
	while (++cpt <= len)
		if (*(s + cpt) == c)
			return ((char *)(s + cpt));
	return (0);
}
