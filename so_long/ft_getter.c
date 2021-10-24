/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:21:53 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 16:25:36 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_getcoin(t_vars *t)
{
	int	x;
	int	y;

	y = -1;
	while (++y < t->rezy)
	{
		x = -1;
		while (++x < t->rezx)
		{
			if (t->map[y][x].type == 'C')
				t->map[y][x].img.img = ft_path_to_img(COIN_PATH,
						t, t->map[y][x].type);
		}
	}
}

static void	ft_getexit(t_vars *t)
{
	int	x;
	int	y;

	y = -1;
	while (++y < t->rezy)
	{
		x = -1;
		while (++x < t->rezx)
		{
			if (t->map[y][x].type == 'E')
				t->map[y][x].img.img = ft_path_to_img(EXIT_PATH,
						t, t->map[y][x].type);
		}
	}
}

static void	ft_getwall(t_vars *t)
{
	int	x;
	int	y;

	y = -1;
	while (++y < t->rezy)
	{
		x = -1;
		while (++x < t->rezx)
		{
			if (t->map[y][x].type == '1')
				t->map[y][x].img.img = ft_path_to_img(WALL_PATH,
						t, t->map[y][x].type);
		}
	}
}

static void	ft_gethero(t_vars *t)
{
	int	x;
	int	y;
	int	f;

	y = -1;
	f = 1;
	while (++y < t->rezy && f)
	{
		x = -1;
		while (++x < t->rezx && f)
		{
			if (t->map[y][x].type == 'P')
			{
				t->map[y][x].img.img = ft_path_to_img(HERO_PATH,
						t, t->map[y][x].type);
				t->hero.x_pos = x;
				t->hero.y_pos = y;
				f = -1;
			}
		}
	}
}

void	ft_getall(t_vars *t)
{
	ft_getcoin(t);
	ft_getwall(t);
	ft_getexit(t);
	ft_gethero(t);
}
