/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:09:42 by dzuntini          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:34 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *s, const char *n, size_t len)
{
	size_t	istr;
	size_t	itfnd;
	size_t	srchi;

	if (n[0] == '\0')
		return ((char *)s);
	istr = 0;
	while (s[istr] != '\0' && istr < len)
	{
		if (s[istr] == n[0])
		{
			itfnd = 0;
			srchi = istr;
			while ((s[srchi] != '\0') && (srchi < len && s[srchi] == n[itfnd]))
			{
				itfnd++;
				srchi++;
				if (n[itfnd] == '\0')
					return ((char *)&s[istr]);
			}
		}
		istr++;
	}
	return (0);
}
