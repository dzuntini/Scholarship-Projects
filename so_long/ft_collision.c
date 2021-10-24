/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 19:18:26 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 19:43:12 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_coll(t_vars *t, int x, int y)
{
	if (t->map[y][x].type == '1')
		return (-1);
	if (t->map[y][x].type == 'E')
	{
		if (t->colcoin == t->nbcoin)
		{
			printf("Congrats you win in %i moves!!!\n", t->nbmov);
			freemap(t, 0);
		}
		else
			return (-1);
	}
	else if (t->map[y][x].type == 'C')
	{
		t->colcoin++;
		t->map[y][x].type = '0';
		t->nbmov++;
	}
	else
		t->nbmov++;
	return (0);
}
