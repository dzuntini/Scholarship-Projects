/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:11:31 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 19:47:20 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"so_long.h"

static int	ft_checkforspec(t_vars *t)
{
	int	x;
	int	y;
	int	h;
	int	e;

	y = -1;
	e = 0;
	h = 0;
	t->nbcoin = 0;
	while (++y < t->rezy)
	{
		x = -1;
		while (++x < t->rezx)
		{
			if (t->map[y][x].type == 'C')
				t->nbcoin++;
			if (t->map[y][x].type == 'E')
				e++;
			if (t->map[y][x].type == 'P')
				h++;
		}
	}
	if (t->nbcoin == 0 || h != 1 || e != 1)
		return (-1);
	return (1);
}

int	ft_mapcheck(t_vars *t)
{
	int	i;

	i = -1;
	while (++i < t->rezy)
	{
		if (t->map[i][0].type != '1' && t->map[i][t->rezx - 1].type != '1')
			return (-1);
	}
	return (ft_checkforspec(t));
}

int	ft_charchecker(const char *str)
{
	static char	set[6] = "01CEP";
	int			i;
	int			s;

	i = 0;
	while (str[i])
	{
		s = 0;
		while (set[s])
		{
			if (str[i] == set[s])
				break ;
			s++;
		}
		if (set[s] == '\0')
			break ;
		else
			i++;
	}
	if (str[i] == '\0')
		return (1);
	return (-1);
}

void	*ft_path_to_img(char *path, t_vars *t, int type)
{
	static void	*img;
	static int	i = 0;

	if (type != i)
	{
		i = open(path, O_RDONLY);
		if (i != -1)
		{
			img = mlx_xpm_file_to_image(t->mlx, path, &t->img_size,
					&t->img_size);
			close(i);
		}
		else
		{
			ft_putstr_fd("ERROR : Can\'t find file\n", 2);
			exit(0);
		}
		i = type;
	}
	return (img);
}
