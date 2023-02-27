/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:09:23 by jrathelo          #+#    #+#             */
/*   Updated: 2022/04/25 11:31:02 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// 0 is south, 1 is east, 2 is north and 3 is west
void	var_set_direction(t_cub *cub, int dir)
{
	if (dir == 'E')
	{
		cub->corddata.dir.x = 1;
		cub->corddata.dir.y = 0;
		cub->corddata.plane.x = 0;
		cub->corddata.plane.y = -0.66;
	}
	if (dir == 'S')
	{
		cub->corddata.dir.x = 0;
		cub->corddata.dir.y = 1;
		cub->corddata.plane.x = 0.66;
		cub->corddata.plane.y = 0;
	}
	var_set_direction2(cub, dir);
}

void	var_set_direction2(t_cub *cub, int dir)
{
	if (dir == 'W')
	{
		cub->corddata.dir.x = -1;
		cub->corddata.dir.y = 0;
		cub->corddata.plane.x = 0;
		cub->corddata.plane.y = 0.66;
	}
	if (dir == 'N')
	{
		cub->corddata.dir.x = 0;
		cub->corddata.dir.y = -1;
		cub->corddata.plane.x = -0.66;
		cub->corddata.plane.y = 0;
	}
}

static void	var_init(t_cub *cub)
{
	cub->fflags.xntext = false;
	cub->fflags.xstext = false;
	cub->fflags.xetext = false;
	cub->fflags.xwtext = false;
	cub->fflags.map = false;
	cub->fflags.parsed = false;
	cub->fflags.text_tab = false;
	cub->fflags.sf = false;
	cub->fflags.sky = false;
	cub->fflags.floor = false;
	cub->data.mwidth = 0;
	cub->mm.oldnav.y = -13845;
	cub->mm.oldnav.x = 8754;
	init_textures(cub);
}

int	main(int ac, char **av)
{
	t_cub		cub;
	t_img_data	img;

	(void) av;
	if (ac == 2)
	{
		var_init(&cub);
		cub.mlx = mlx_init();
		cub_map_init(av[1], &cub);
		cub.win = mlx_new_window(cub.mlx, SWID, SHGHT, "cub3d");
		img.img = mlx_new_image(cub.mlx, SWID, SHGHT);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		cub.img = img;
		var_set_direction(&cub, cub.data.dir);
		raycast(&cub);
		minimap(&cub);
		mlx_put_image_to_window(cub.mlx, cub.win, cub.img.img, 0, 0);
		mlx_hook(cub.win, 2, 1L << 0, &cub_key_press, &cub);
		mlx_hook(cub.win, 17, 1L << 17, &cub_close_prog, &cub);
		mlx_loop(cub.mlx);
	}
	else
		ft_putstr("Usage : ./cub3d XX.cub");
	return (0);
}
