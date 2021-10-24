/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:19:43 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 16:21:30 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	sethero(t_vars *t)
{
	mlx_put_image_to_window(t->mlx, t->win, t->hero.img.img,
		(t->hero.x_pos * 16), (t->hero.y_pos * 16));
}

static void	setothers(t_vars *t)
{
	int	x;
	int	y;

	y = -1;
	while (++y < t->rezy)
	{
		x = -1;
		while (++x < t->rezx)
		{
			if (t->map[y][x].type != '0' && t->map[y][x].type != 'P')
				mlx_put_image_to_window(t->mlx, t->win, t->map[y][x].img.img,
					(x * t->img_size), (y * t->img_size));
		}
	}
}

void	ft_setall(t_vars *t)
{
	sethero(t);
	setothers(t);
}
