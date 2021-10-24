/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:13:38 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/14 16:15:44 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iferror(int cond, char *string)
{
	if (!cond)
	{
		ft_puterr(string);
		return (-1);
	}
	return (1);
}

int	ft_iferrorfree(int cond, char *string, void *fr)
{
	if (cond)
	{
		ft_puterr(string);
		free(fr);
		return (-1);
	}
	return (1);
}
