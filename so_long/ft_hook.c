/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:59:26 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 19:41:27 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	hero_hook(int keycode, t_vars *t)
{
	if (keycode == 123)
	{
		if (t->hero.x_pos > 0
			&& !(ft_coll(t, t->hero.x_pos - 1, t->hero.y_pos)))
			t->hero.x_pos--;
	}
	if (keycode == 124)
	{
		if (t->hero.x_pos < (t->rezx - 1)
			&& !(ft_coll(t, t->hero.x_pos + 1, t->hero.y_pos)))
			t->hero.x_pos++;
	}
	if (keycode == 126)
	{
		if (t->hero.y_pos > 0
			&& !(ft_coll(t, t->hero.x_pos, t->hero.y_pos - 1)))
			t->hero.y_pos--;
	}
	if (keycode == 125)
	{
		if (t->hero.y_pos < (t->rezy - 1)
			&& !(ft_coll(t, t->hero.x_pos, t->hero.y_pos + 1)))
			t->hero.y_pos++;
	}
}

int	exit_hook(t_vars *t)
{
	ft_putstr("So long and Thanks for the fish\n");
	freemap(t, 0);
	exit(0);
}

int	key_hook(int keycode, t_vars *t)
{
	refresh(*t);
	if (keycode == 54 || keycode == 53)
		exit_hook(t);
	hero_hook(keycode, t);
	mlx_put_image_to_window(t->mlx, t->win, t->hero.img.img,
		(t->hero.x_pos * 16), (t->hero.y_pos * 16));
	mlx_string_put(t->mlx, t->win, 0, 0, 16724787, ft_itoa(t->nbmov));
	ft_putstrr(ft_itoa(t->nbmov));
	return (1);
}
