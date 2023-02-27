/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeandexit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:36:58 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/21 12:35:35 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_errfreeandexit(char *str, t_cub *cub, int code)
{
	ft_puterr(str);
	ft_freeandexit(cub, code);
}

void	ft_freeandexit(t_cub *cub, int code)
{
	if (cub->fflags.xntext)
		free(cub->data.xntext.img);
	if (cub->fflags.xstext)
		free(cub->data.xstext.img);
	if (cub->fflags.xetext)
		free(cub->data.xetext.img);
	if (cub->fflags.xwtext)
		free(cub->data.xwtext.img);
	if (cub->fflags.parsed)
		ft_freetab(cub->data.parsed);
	if (cub->fflags.sf)
		ft_freetab(cub->data.sf);
	if (cub->fflags.text_tab)
		ft_freetab(cub->data.text_tab);
	exit(code);
}
/*if (cub->fflags.map) Seems to get freed
ft_freetab(cub->data.map);*/