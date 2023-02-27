/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:13:38 by dzuntini          #+#    #+#             */
/*   Updated: 2022/03/30 18:21:34 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
