/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:00:08 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 19:55:44 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	freemap(t_vars *t, int m)
{
	int	y;

	y = -1;
	if (m == 0)
		mlx_destroy_window(t->mlx, t->win);
	while (++y < t->rezy)
		free(t->map[y]);
	free(t->map);
	exit(0);
}
