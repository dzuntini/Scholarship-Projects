/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrathelo <jrathelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 17:23:27 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/19 10:50:08 by jrathelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	bordercheck(char *s, t_cub *cub)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == 0)
			break ;
		if (s[i] != '1')
			ft_errfreeandexit("Trou dans la map", cub, -1);
		i++;
	}
}

static void	middlecheck(char *s, t_cub *cub)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] != '1' || s[ft_strlen(s) - 1] != '1')
		ft_errfreeandexit("Trou dans la map", cub, -1);
}

static void	count_player(t_cub *cub)
{
	int		i;
	int		j;
	char	a;

	i = -1;
	a = '0';
	while (cub->data.map[++i])
	{
		j = -1;
		while (cub->data.map[i][++j])
		{
			if (check_letter(cub->data.map[i][j], "NEWS"))
			{
				if (a != '0')
					ft_errfreeandexit("Too many players on the map", cub, -1);
				a = cub->data.map[i][j];
				cub->corddata.pos.x = j + 0.01;
				cub->corddata.pos.y = i + 0.01;
				cub->data.map[i][j] = '0';
			}
		}
	}
	cub->data.dir = a;
}

void	check_border(t_cub *cub)
{
	int	i;

	i = -1;
	bordercheck(cub->data.map[0], cub);
	bordercheck(cub->data.map[cub->data.mheight - 1], cub);
	while (cub->data.map[++i] != NULL)
		middlecheck(cub->data.map[i], cub);
}

void	final_check(t_cub *cub)
{
	count_player(cub);
	check_border(cub);
	check_closed_walls(cub);
}
