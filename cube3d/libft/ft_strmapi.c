/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:26:15 by dzuntini          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:34 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	if (s)
	{
		res = ft_calloc((ft_strlen(s) + 1), sizeof(char));
		if (res == NULL)
			return (NULL);
		i = 0;
		while (s[i])
		{
			res[i] = (*f)(i, ((char)s[i]));
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
