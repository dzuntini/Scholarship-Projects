/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:22 by dzuntini          #+#    #+#             */
/*   Updated: 2022/04/19 15:29:57 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
 *
 * NO ./path_to_the_north_texture
 * SO ./path_to_the_south_texture
 * WE ./path_to_the_west_texture
 * EA ./path_to_the_east_texture
 * F 220,100,0
 * C 225,30,0
 *	MAP ;
 */

static void	end_parse(t_cub *cub, int i, int e)
{
	int	f;

	f = e - i;
	cub->data.map = malloc((f + 1) * sizeof(char *));
	cub->fflags.map = true;
	f = 0;
	while (cub->data.parsed[i] != NULL)
	{
		if (!check_letter_line(cub->data.parsed[i], "01 \tNEWS"))
			ft_errfreeandexit("Incorrect character in the map", cub, -1);
		cub->data.map[f] = strdup(cub->data.parsed[i++]);
		if (ft_strlen(cub->data.map[f]) > cub->data.mwidth)
			cub->data.mwidth = ft_strlen(cub->data.map[f]);
		f++;
	}
	cub->data.mheight = f;
	cub->data.map[f] = NULL;
	final_check(cub);
}

static void	get_map(int begin, t_cub *cub)
{
	int	end;

	end = begin;
	if (begin == -1)
		ft_errfreeandexit("Map not found", cub, -1);
	while (cub->data.parsed[end++] != NULL)
		;
	end_parse(cub, begin, end);
}

static int	get_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->data.parsed[i])
	{
		if (check_begin(cub->data.parsed[i], "NO "))
			param_parse(cub->data.parsed[i], cub);
		else if (check_begin(cub->data.parsed[i], "SO "))
			param_parse(cub->data.parsed[i], cub);
		else if (check_begin(cub->data.parsed[i], "WE "))
			param_parse(cub->data.parsed[i], cub);
		else if (check_begin(cub->data.parsed[i], "EA "))
			param_parse(cub->data.parsed[i], cub);
		else if (check_begin(cub->data.parsed[i], "F "))
			param_parse(cub->data.parsed[i], cub);
		else if (check_begin(cub->data.parsed[i], "C "))
			param_parse(cub->data.parsed[i], cub);
		else if (check_letter_line(cub->data.parsed[i], "01 NEWS"))
			return (i);
		i++;
	}
	return (-1);
}

void	cub_map_init(char *path, t_cub *cub)
{
	int		fd;
	char	buff[2];
	char	*parse;
	int		br;

	if (ft_check_end(path, ".cub") == 0)
		ft_puterrexit("Wrong Extension", -1);
	else
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_puterrexit("Can't Open File", fd);
		br = read(fd, buff, 1);
		parse = ft_read_loop(br, buff, fd);
		cub->data.parsed = ft_split(parse, '\n');
		cub->fflags.parsed = true;
		replace_letter(cub, '\t', ' ');
		free(parse);
		close(fd);
		get_map(get_textures(cub), cub);
		if ((cub->fflags.xntext + cub->fflags.xstext
				+ cub->fflags.xntext + cub->fflags.xstext
				+ cub->fflags.floor + cub->fflags.sky) < 6)
			ft_errfreeandexit("Lacking Texture", cub, -1);
	}
}
