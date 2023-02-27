/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:18:26 by jrathelo          #+#    #+#             */
/*   Updated: 2022/04/19 16:01:58 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	cub_rotate_right(t_cub *vars)
{
	double	olddir;
	double	oldplane;
	double	rspeed;

	olddir = vars->corddata.dir.x;
	oldplane = vars->corddata.plane.x;
	rspeed = 0.02 * M_PI;
	vars->corddata.dir.x = vars->corddata.dir.x * cos(rspeed)
		- vars->corddata.dir.y * sin(rspeed);
	vars->corddata.dir.y = olddir * sin(rspeed)
		+ vars->corddata.dir.y * cos(rspeed);
	vars->corddata.plane.x = vars->corddata.plane.x * cos(rspeed)
		- vars->corddata.plane.y * sin(rspeed);
	vars->corddata.plane.y = oldplane * sin(rspeed)
		+ vars->corddata.plane.y * cos(rspeed);
}

void	cub_rotate_left(t_cub *vars)
{
	double	olddir;
	double	oldplane;
	double	rspeed;

	olddir = vars->corddata.dir.x;
	oldplane = vars->corddata.plane.x;
	rspeed = 0.02 * M_PI;
	vars->corddata.dir.x = vars->corddata.dir.x * cos(-rspeed)
		- vars->corddata.dir.y * sin(-rspeed);
	vars->corddata.dir.y = olddir * sin(-rspeed)
		+ vars->corddata.dir.y * cos(-rspeed);
	vars->corddata.plane.x = vars->corddata.plane.x * cos(-rspeed)
		- vars->corddata.plane.y * sin(-rspeed);
	vars->corddata.plane.y = oldplane * sin(-rspeed)
		+ vars->corddata.plane.y * cos(-rspeed);
}

void	cub_move_forward(t_cub *vars)
{
	t_cords	next;

	next.x = vars->corddata.pos.x + vars->corddata.dir.x * 0.5;
	next.y = vars->corddata.pos.y + vars->corddata.dir.y * 0.5;
	if (!(next.x < 0 || next.x > vars->data.mwidth || next.y < 0
			|| next.y > vars->data.mheight))
	{
		if (vars->data.map[(int) next.y][(int) next.x] == '0')
		{
			vars->corddata.pos.x = next.x;
			vars->corddata.pos.y = next.y;
		}
	}
}

void	cub_move_backwards(t_cub *vars)
{
	t_cords	next;

	next.x = vars->corddata.pos.x - vars->corddata.dir.x * 0.5;
	next.y = vars->corddata.pos.y - vars->corddata.dir.y * 0.5;
	if (!(next.x < 0 || next.x > vars->data.mwidth || next.y < 0
			|| next.y > vars->data.mheight))
	{
		if (vars->data.map[(int) next.y][(int) next.x] == '0')
		{
			vars->corddata.pos.x = next.x;
			vars->corddata.pos.y = next.y;
		}
	}
}

// code to move around the map W and S move the player forward or backwards, 
// a simple check exists also to prevent walking through walls
void	cub_move_arround(int keycode, t_cub *vars)
{
	if (keycode == W || keycode == U_ARROW)
		cub_move_forward(vars);
	else if (keycode == S || keycode == D_ARROW)
		cub_move_backwards(vars);
	else if (keycode == L_ARROW)
		cub_rotate_left(vars);
	else if (keycode == R_ARROW)
		cub_rotate_right(vars);
	else if (keycode == A)
		cub_strafe_left(vars);
	else if (keycode == D)
		cub_strafe_right(vars);
	raycast(vars);
	minimap(vars);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
