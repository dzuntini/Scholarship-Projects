/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 11:22:39 by dzuntini          #+#    #+#             */
/*   Updated: 2021/08/22 22:11:56 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		cpt;
	char	*ret;

	cpt = 0;
	ret = malloc(ft_strlen(s) + 1);
	if (!ret)
		return (0);
	while (s[cpt])
	{
		ret[cpt] = f(cpt, s[cpt]);
		cpt++;
	}
	ret[cpt] = '\0';
	return (ret);
}
