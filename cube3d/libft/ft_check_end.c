/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:12:06 by dzuntini          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:34 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_check_end(char *file, char *ext)
{
	int	f;
	int	e;

	if (file[0] != '\0')
	{
		if ((ft_strlen(file) - ft_strlen(ext)) <= 0)
			return (0);
		f = ft_strlen(file) - ft_strlen(ext);
		e = 0;
		while (file[f] == ext[e] && file[f] != '\0')
		{
			f++;
			e++;
		}
		if (ext[e] == '\0')
			return (1);
	}
	return (0);
}
