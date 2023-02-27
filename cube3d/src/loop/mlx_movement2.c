/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_movement2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:31:16 by jrathelo          #+#    #+#             */
/*   Updated: 2022/04/19 16:02:10 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	cub_strafe_right(t_cub *vars)
{
	t_cords	next;
	t_cords	sidedir;

	sidedir.x = -vars->corddata.dir.y;
	sidedir.y = vars->corddata.dir.x;
	next.x = vars->corddata.pos.x + sidedir.x * 0.5;
	next.y = vars->corddata.pos.y + sidedir.y * 0.5;
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

void	cub_strafe_left(t_cub *vars)
{
	t_cords	next;
	t_cords	sidedir;

	sidedir.x = vars->corddata.dir.y;
	sidedir.y = -vars->corddata.dir.x;
	next.x = vars->corddata.pos.x + sidedir.x * 0.5;
	next.y = vars->corddata.pos.y + sidedir.y * 0.5;
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
