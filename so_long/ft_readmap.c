/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:36:53 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 19:40:04 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	first_open(char *file, t_vars *t)
{
	char	*str;
	int		fd;
	int		tmp;

	fd = open(file, O_RDONLY);
	if (!ft_iferror(fd, "Error: Incorrect File"))
		exit (-1);
	str = malloc(BUFFER_SIZE * sizeof(char));
	t->rezx = get_next_line(fd, &str);
	if (ft_iferrorfree((t->rezx <= 2),
			"Error: Map dimension incorrect", str) == -1)
		exit (-1);
	tmp = t->rezx;
	t->rezy = 0;
	while (tmp > 0)
	{
		if (ft_iferrorfree((tmp != t->rezx),
				"Error: Map dimension incorrect", str) == -1)
			exit(0);
		t->rezy++;
		tmp = get_next_line(fd, &str);
	}
	free(str);
	close(fd);
}

static int	parsing_map(t_vars *t, char *str, int y)
{
	int	i;

	i = 0;
	if (ft_charchecker(str) == 1)
	{
		while (str[i] != '\0')
		{
			if (y == 0 || y == (t->rezy - 1))
				if (str[i] != '1')
					return (-1);
			t->map[y][i].type = str[i];
			i++;
		}
	}
	else
		return (-1);
	return (1);
}

static void	sec_open(char *file, t_vars *t)
{
	char	*str;
	int		fd;
	int		tmp;
	int		y;

	fd = open(file, O_RDONLY);
	str = malloc(BUFFER_SIZE * sizeof(char));
	tmp = get_next_line(fd, &str);
	y = 0;
	while (tmp > 0)
	{
		if ((parsing_map(t, str, y)) == -1)
		{
			ft_puterr("Error:Caractere Invalide");
			free(str);
			freemap(t, 1);
		}
		tmp = get_next_line(fd, &str);
		y++;
	}
	close(fd);
	free(str);
}

void	ft_readmap(char *file, t_vars *t)
{
	int	i;

	if (ft_check_end(file, ".ber"))
	{
		first_open(file, t);
		t->map = ft_malloc(t->rezy * sizeof(t_char *));
		i = 0;
		while (i < t->rezy)
			t->map[i++] = ft_malloc(t->rezx * sizeof(t_char) + 1);
		sec_open(file, t);
		if (ft_mapcheck(t) == -1)
		{
			ft_puterr("Error: Map Invalide");
			freemap(t, 1);
		}
		t->sr.resy = t->rezy * 16;
		t->sr.resx = t->rezx * 16;
	}
	else
	{
		ft_puterr("Error : Incorrect File");
		exit(0);
	}
}
