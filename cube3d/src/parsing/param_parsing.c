/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:32:51 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/21 12:44:42 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_textures(t_cub *cub)
{
	cub->data.xntext.img = NULL;
	cub->data.xstext.img = NULL;
	cub->data.xetext.img = NULL;
	cub->data.xwtext.img = NULL;
}

static void	check_textures(const char *str, char c, t_cub *cub)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_errfreeandexit("Can't Open Texture File", cub, -1);
	if (c == 'N')
		n_put(cub, (char *)str);
	if (c == 'S')
		s_put(cub, (char *)str);
	if (c == 'E')
		e_put(cub, (char *)str);
	if (c == 'W')
		w_put(cub, (char *)str);
}

int	param_parse(const char *str, t_cub *cub)
{
	char	c;

	cub->data.text_tab = ft_split(str, ' ');
	cub->fflags.text_tab = true;
	c = cub->data.text_tab[0][0];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (check_tabsize(cub->data.text_tab, 2) == false)
			ft_errfreeandexit("Too much stuff in texture line", cub, -1);
		check_textures(cub->data.text_tab[1], c, cub);
	}
	if (c == 'F' || c == 'C')
	{
		if (check_tabsize(cub->data.text_tab, 2) == false)
			ft_errfreeandexit("Error with RGB values", cub, -1);
		cub->data.sf = ft_split(cub->data.text_tab[1], ',');
		cub->fflags.sky = true;
		skyndfloor(c, cub);
		freestuff('s', cub);
	}
	freestuff('t', cub);
	return (true);
}
