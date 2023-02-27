/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:22:36 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/17 17:37:06 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// RED is pos , Black is empty , White is wall
static void	fillmap(int color, t_cub *cub)
{
	t_cordsi	a;
	int			y;
	int			x;

	y = -1;
	while (++y < 8)
	{
		x = -1;
		while (++x < 8)
		{
			a.y = cub->mm.minicasecoord.y + y;
			a.x = cub->mm.minicasecoord.x + x;
			draw_pixel(&cub->img, a, color);
		}
	}
}

void	get_pos(t_cub *cub)
{
	static int	x = -5;
	static int	y = -5;
	size_t		tx;
	size_t		ty;

	tx = cub->corddata.pos.x + x;
	ty = cub->corddata.pos.y + y;
	if (ty < 0 || !(ty < cub->data.mheight)
		|| tx < 0 || !(tx < ft_strlen(cub->data.map[ty])))
		fillmap(WHITE, cub);
	else
	{
		if (!y && !x)
			fillmap(RED, cub);
		else if (cub->data.map[ty][tx] == '1')
			fillmap(WHITE, cub);
		else
			fillmap(BLACK, cub);
	}
	if (++x == 6 && ++y == 6)
		y = -5;
	if (x == 6)
		x = -5;
}

void	minimap(t_cub *cub)
{
	int			y;
	int			x;
	const int	casesize = 8;

	y = -1;
	while (++y < 11)
	{
		x = -1;
		cub->mm.minicasecoord.y = y * casesize;
		while (++x < 11)
		{
			cub->mm.minicasecoord.x = x * casesize;
			get_pos(cub);
		}
	}
}
