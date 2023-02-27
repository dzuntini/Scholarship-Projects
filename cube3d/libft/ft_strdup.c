/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 09:33:35 by dzuntini          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:34 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		i;

	i = 0;
	while (src[i] != '\0')
		i++;
	cpy = malloc(i * sizeof(char));
	if (cpy != NULL)
	{
		i = 0;
		while (src[i] != '\0')
		{
			cpy[i] = src[i];
			i++;
		}
		cpy[i] = '\0';
	}
	return (cpy);
}
