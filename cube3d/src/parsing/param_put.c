/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:32:51 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/21 12:26:05 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	skyndfloor(char c, t_cub *cub)
{
	int	i;
	int	t;

	i = 0;
	if (check_tabsize(cub->data.sf, 3) == false)
		ft_errfreeandexit("RGB values error", cub, -1);
	while (cub->data.sf[i])
	{	
		t = ft_atoi2(cub->data.sf[i]);
		if (t == -1)
			ft_errfreeandexit("Error with RGB values", cub, -1);
		if (c == 'F')
		{
			cub->fflags.floor = true;
			cub->data.floor[i] = t;
		}
		else if (c == 'C')
		{
			cub->fflags.sky = true;
			cub->data.sky[i] = t;
		}
		i++;
	}
	if (i < 3)
		ft_errfreeandexit("RGB values error", cub, -1);
}

void	n_put(t_cub *cub, char *str)
{
	if (cub->data.xntext.img != NULL)
		ft_errfreeandexit("Two times the same texture", cub, -1);
	cub->data.xntext.img = mlx_xpm_file_to_image(cub->mlx,
			str, &cub->data.xntext.textwidth, &cub->data.xntext.textheight);
	if (cub->data.xntext.img == NULL)
		ft_errfreeandexit("Cannot add xpm of north texture", cub, -1);
	cub->data.xntext.addr = mlx_get_data_addr(cub->data.xntext.img,
			&(cub->data.xntext.bits_per_pixel),
			&(cub->data.xntext.line_length), &(cub->data.xntext.endian));
	cub->fflags.xntext = true;
}

void	s_put(t_cub *cub, char *str)
{
	if (cub->data.xstext.img != NULL)
		ft_errfreeandexit("Two times the same texture", cub, -1);
	cub->data.xstext.img = mlx_xpm_file_to_image(cub->mlx,
			str, &cub->data.xstext.textwidth, &cub->data.xstext.textheight);
	if (cub->data.xstext.img == NULL)
		ft_errfreeandexit("Cannot add xpm of south texture", cub, -1);
	cub->data.xstext.addr = mlx_get_data_addr(cub->data.xstext.img,
			&(cub->data.xstext.bits_per_pixel),
			&(cub->data.xstext.line_length), &(cub->data.xstext.endian));
	cub->fflags.xstext = true;
}

void	e_put(t_cub *cub, char *str)
{
	if (cub->data.xetext.img != NULL)
		ft_errfreeandexit("Two times the same texture", cub, -1);
	cub->data.xetext.img = mlx_xpm_file_to_image(cub->mlx,
			str, &cub->data.xetext.textwidth, &cub->data.xetext.textheight);
	if (cub->data.xetext.img == NULL)
		ft_errfreeandexit("Cannot add xpm of east texture", cub, -1);
	cub->data.xetext.addr = mlx_get_data_addr(cub->data.xetext.img,
			&(cub->data.xetext.bits_per_pixel),
			&(cub->data.xetext.line_length), &(cub->data.xetext.endian));
	cub->fflags.xetext = true;
}

void	w_put(t_cub *cub, char *str)
{
	if (cub->data.xwtext.img != NULL)
		ft_errfreeandexit("Two times the same texture", cub, -1);
	cub->data.xwtext.img = mlx_xpm_file_to_image(cub->mlx,
			str, &cub->data.xwtext.textwidth, &cub->data.xwtext.textheight);
	if (cub->data.xwtext.img == NULL)
		ft_errfreeandexit("Cannot add xpm of west texture", cub, -1);
	cub->data.xwtext.addr = mlx_get_data_addr(cub->data.xwtext.img,
			&(cub->data.xwtext.bits_per_pixel),
			&(cub->data.xwtext.line_length), &(cub->data.xwtext.endian));
	cub->fflags.xwtext = true;
}
