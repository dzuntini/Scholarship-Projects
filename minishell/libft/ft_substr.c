/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 08:38:39 by dzuntini          #+#    #+#             */
/*   Updated: 2021/08/22 22:12:48 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	ret = malloc(len + 1);
	if (!ret)
		return (0);
	if ((int)start >= ft_strlen(s))
	{
		ret[0] = '\0';
	}
	else
	{
		ft_strlcpy(ret, s + start, len + 1);
	}
	return (ret);
}
