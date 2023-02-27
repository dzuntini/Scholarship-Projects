/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:27:33 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/25 11:32:02 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_surrounded(t_cub *cub, int i, int x)
{
	if (cub->data.map[i][x + 1] != ' '
		&& cub->data.map[i][x - 1] != ' '
		&& cub->data.map[i + 1][x] != ' '
		&& cub->data.map[i - 1][x] != ' '
		&& cub->data.map[i + 1][x + 1] != ' '
		&& cub->data.map[i + 1][x - 1] != ' '
		&& cub->data.map[i - 1][x + 1] != ' '
		&& cub->data.map[i - 1][x - 1] != ' ')
		return (1);
	return (0);
}

void	check_closed_walls(t_cub *cub)
{
	int	i;
	int	x;
	int	save;

	i = 0;
	save = 0;
	while (cub->data.map[i])
	{
		if ((int)ft_strlen(cub->data.map[i]) - 1 < save)
			ft_errfreeandexit("Trou dans la map", cub, -1);
		x = 0;
		save = 0;
		while (cub->data.map[i][x])
		{
			if (cub->data.map[i][x] == '0')
			{
				if (check_surrounded(cub, i, x) == 0)
					ft_errfreeandexit("Trou dans la map", cub, -1);
				save = x;
			}
			x++;
		}
		i++;
	}
}

int	check_begin(const char *s, const char *b)
{
	int	i;

	i = 0;
	while (s[i] && b[i])
	{
		if (s[i] != b[i])
			break ;
		i++;
	}
	if (b[i] == '\0')
		return (true);
	return (false);
}

char	*ft_read_loop(int bytesred, char buff[2], int fd)
{
	char	*tmp;
	char	*str;

	str = NULL;
	while (bytesred > 0)
	{
		buff[bytesred] = '\0';
		if (str == NULL)
			str = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str, buff);
			free (str);
			str = tmp;
		}
		bytesred = read(fd, buff, 1);
	}
	return (str);
}

int	check_tabsize(char **tab, int size)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	if (i != size)
		return (false);
	return (true);
}
