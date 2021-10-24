/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:12:06 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/14 16:12:52 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_end(char *file, char *ext)
{
	int	f;
	int	e;

	if (file[0] != '\0')
	{
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
