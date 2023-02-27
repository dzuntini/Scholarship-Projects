/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1011/01/10 11:11:11 by jrathelo          #+#    #+#             */
/*   Updated: 2022/04/19 15:38:38 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	initiation_1(t_cub *cub, double camera)
{
	cub->corddata.raydir.x = cub->corddata.dir.x
		+ cub->corddata.plane.x * camera;
	cub->corddata.raydir.y = cub->corddata.dir.y
		+ cub->corddata.plane.y * camera;
	cub->corddata.mappos.x = (int) cub->corddata.pos.x;
	cub->corddata.mappos.y = (int) cub->corddata.pos.y;
	if (cub->corddata.raydir.x == 0)
		cub->corddata.deltadist.x = LLONG_MAX;
	else
		cub->corddata.deltadist.x = fabs(1 / cub->corddata.raydir.x);
	if (cub->corddata.raydir.y == 0)
		cub->corddata.deltadist.y = LLONG_MAX;
	else
		cub->corddata.deltadist.y = fabs(1 / cub->corddata.raydir.y);
}

void	initiation_2(t_cub *cub)
{
	if (cub->corddata.raydir.x < 0)
	{
		cub->corddata.step.x = -1;
		cub->corddata.sidedist.x = (cub->corddata.pos.x
				- cub->corddata.mappos.x) * cub->corddata.deltadist.x;
	}
	else
	{
		cub->corddata.step.x = 1;
		cub->corddata.sidedist.x = (cub->corddata.mappos.x + 1.0
				- cub->corddata.pos.x) * cub->corddata.deltadist.x;
	}
	if (cub->corddata.raydir.y < 0)
	{
		cub->corddata.step.y = -1;
		cub->corddata.sidedist.y = (cub->corddata.pos.y
				- cub->corddata.mappos.y) * cub->corddata.deltadist.y;
	}
	else
	{
		cub->corddata.step.y = 1;
		cub->corddata.sidedist.y = (cub->corddata.mappos.y + 1.0
				- cub->corddata.pos.y) * cub->corddata.deltadist.y;
	}
}

int	dda(t_cub *cub, char **world)
{
	int	side;

	while (1)
	{
		if (cub->corddata.sidedist.x < cub->corddata.sidedist.y)
		{
			cub->corddata.sidedist.x += cub->corddata.deltadist.x;
			cub->corddata.mappos.x += cub->corddata.step.x;
			side = 0;
			if (cub->corddata.step.x > 0)
				side = 2;
		}
		else
		{
			cub->corddata.sidedist.y += cub->corddata.deltadist.y;
			cub->corddata.mappos.y += cub->corddata.step.y;
			side = 3;
			if (cub->corddata.step.y > 0)
				side = 1;
		}
		if (world[(int) cub->corddata.mappos.y][(int) cub->corddata.mappos.x]
				== '1')
			return (side);
	}
	return (-1);
}

void	calculate_draw_lines(t_cub *cub, double walldist, int x, int side)
{
	t_raycasy_line	line;

	line.lineheight = (int)(SHGHT / walldist);
	line.drawstart = -line.lineheight / 2 + SHGHT / 2;
	line.drawend = line.lineheight / 2 + SHGHT / 2;
	line.side = side;
	if (side == 0 || side == 2)
		line.wallpos = cub->corddata.pos.y + walldist * cub->corddata.raydir.y;
	else
		line.wallpos = cub->corddata.pos.x + walldist * cub->corddata.raydir.x;
	line.wallpos -= floor(line.wallpos);
	draw_raycast_line(cub, line, x);
}

void	raycast(t_cub *cub)
{
	double	camera;
	int		side;
	int		x;
	double	walldist;

	x = 0;
	while (x < SWID)
	{	
		camera = 2 * x / (double) SWID - 1;
		initiation_1(cub, camera);
		initiation_2(cub);
		side = dda(cub, cub->data.map);
		if (side == 0 || side == 2)
			walldist = (cub->corddata.sidedist.x - cub->corddata.deltadist.x);
		else
			walldist = (cub->corddata.sidedist.y - cub->corddata.deltadist.y);
		calculate_draw_lines(cub, walldist, x, side);
		x++;
	}
}
