/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:16:57 by jrathelo          #+#    #+#             */
/*   Updated: 2022/04/19 10:18:33 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// Event that is fired whenever a key is pressed, look at cub3d.h for some
// quick refrences to common keys.
int	cub_key_press(int keycode, t_cub *vars)
{
	if (keycode == ESCAPE)
		cub_close_prog(vars);
	else
		cub_move_arround(keycode, vars);
	return (keycode);
}

// Event fired whenever program is closed, frees all data used by the program
int	cub_close_prog(t_cub *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->img.img);
	free(vars->img.addr);
	ft_freeandexit(vars, 0);
	return (0);
}

// Main entrance for mlx loop, hooks are setup here.
void	cub_main_loop(t_cub *cub)
{
	t_img_data	img;

	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SWID, SHGHT, "cub3d");
	img.img = mlx_new_image(cub->mlx, SWID, SHGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	cub->img = img;
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	mlx_hook(cub->win, 2, 1L << 0, &cub_key_press, &cub);
	mlx_hook(cub->win, 17, 0, &cub_close_prog, &cub);
	mlx_loop(cub->mlx);
}
