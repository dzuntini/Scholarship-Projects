/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:48:15 by jrathelo          #+#    #+#             */
/*   Updated: 2022/04/19 16:03:33 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_pixel(t_img_data *d, t_cordsi c, int color)
{
	char	*dst;

	dst = d->addr + (c.y * d->line_length + c.x * (d->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_pixel_from_image(t_img_data *simg, t_cordsi scord,
		t_img_data *iimg, t_cordsi icord)
{
	int		trgb;

	trgb = *(int *)(iimg->addr + (4 * iimg->textwidth
				* icord.y) + (4 * icord.x));
	draw_pixel(simg, scord, trgb);
}

int	create_trgb(int rgb[3])
{
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

// Draws a pixel from the image to the wall
void	draw_line_img(t_cub *cub, t_img_data *img,
		t_raycasy_line line, t_cordsi screen)
{
	t_cordsi	cord;
	int			wallsize;
	double		ratio;

	wallsize = line.drawend - line.drawstart;
	ratio = (double) img->textheight / (double) wallsize;
	cord.y = (screen.y - line.drawstart) * ratio;
	if (cord.y == img->textheight)
		cord.y--;
	cord.x = (int)(line.wallpos * (double) img->textwidth);
	if (line.side == 1 || line.side == 0)
		cord.x = (img->textwidth - 1) - cord.x;
	set_pixel_from_image(&(cub->img), screen, img, cord);
}

// Draws a line depending on what direction
// 0 is south, 1 is east, 2 is north and 3 is west
void	draw_raycast_line(t_cub *cub, t_raycasy_line line, int x)
{
	t_cordsi	c;

	c.x = SWID - x;
	c.y = 0;
	while (c.y < SHGHT)
	{
		if (c.y < line.drawstart)
			draw_pixel(&(cub->img), c, create_trgb(cub->data.sky));
		else if (c.y > line.drawend)
			draw_pixel(&(cub->img), c, create_trgb(cub->data.floor));
		else
		{
			if (line.side == 1)
				draw_line_img(cub, &(cub->data.xstext), line, c);
			else if (line.side == 2)
				draw_line_img(cub, &(cub->data.xwtext), line, c);
			else if (line.side == 3)
				draw_line_img(cub, &(cub->data.xntext), line, c);
			else if (line.side == 0)
				draw_line_img(cub, &(cub->data.xetext), line, c);
		}
		c.y++;
	}
}
