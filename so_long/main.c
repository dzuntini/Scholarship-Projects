/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:09:49 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 16:32:14 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	first_init(t_vars *t)
{
	int	x;
	int	y;

	x = -1;
	while (++x < t->rezx)
	{
		y = -1;
		while (++y < t->rezy)
		{
			mlx_put_image_to_window(t->mlx, t->win, t->map[y][x].img.img,
				(x * t->img_size), (y * t->img_size));
		}
	}
	ft_getall(t);
	ft_setall(t);
}

/*
 ** Init map
 ** Total = Total number of case
 */
static void	map_init(t_vars *t)
{
	int	x;
	int	y;

	y = -1;
	while (++y < t->rezy)
	{
		x = -1;
		while (++x < t->rezx)
			t->map[y][x].img.img = ft_path_to_img(TILE_PATH,
					t, t->map[y][x].type);
	}
	first_init(t);
}

void	refresh(t_vars t)
{
	void	*img;
	int		i;

	i = -1;
	img = ft_path_to_img(TILE_PATH, &t, '0');
	mlx_put_image_to_window(t.mlx, t.win, img,
		(t.hero.x_pos * 16), (t.hero.y_pos * 16));
	while (++i <= 3)
		mlx_put_image_to_window(t.mlx, t.win, t.map[0][i].img.img, (16 * i), 0);
}

int	main(int ac, char **av)
{
	t_vars	t;

	if (ac == 2)
	{
		ft_readmap(av[1], &t);
		t.nbmov = 0;
		t.mlx = mlx_init();
		t.colcoin = 0;
		t.win = mlx_new_window(t.mlx, t.sr.resx, t.sr.resy, "So_Long");
		t.hero.img.img = ft_path_to_img(HERO_PATH, &t, 4);
		mlx_hook(t.win, 2, 1L << 0, key_hook, &t);
		mlx_hook(t.win, 17, 1L << 17, exit_hook, &t);
		map_init(&t);
		mlx_loop(t.mlx);
	}
	else
		ft_puterr("Usage : ./so_long \"XX.ber\"");
}
