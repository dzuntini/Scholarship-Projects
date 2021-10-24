/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:28:27 by dzuntini          #+#    #+#             */
/*   Updated: 2021/10/21 19:37:43 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>

/*
 ** Path
 */
# define TILE_PATH "assets/tile.xpm"
# define HERO_PATH "assets/hero.xpm"
# define WALL_PATH "assets/wall.xpm"
# define COIN_PATH "assets/coin.xpm"
# define EXIT_PATH "assets/exit.xpm"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_img;

typedef struct s_char
{
	t_img	img;
	char	type;
	int		x_pos;
	int		y_pos;
}				t_char;

typedef struct s_rez
{
	int		resy;
	int		resx;

}				t_rez;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		rezx;
	int		rezy;
	t_rez	sr;
	int		img_size;
	int		nbcoin;
	int		colcoin;
	int		nbmov;
	t_char	**map;
	t_char	hero;
}				t_vars;

void	*ft_path_to_img(char *path, t_vars *t, int type);
void	ft_readmap(char *file, t_vars *t);
void	refresh(t_vars t);
void	freemap(t_vars *t, int m);
void	ft_getall(t_vars *t);
void	ft_setall(t_vars *t);

int		ft_charchecker(const char *str);
int		ft_mapcheck(t_vars *t);
int		key_hook(int keycode, t_vars *vars);
int		ft_coll(t_vars *t, int x, int y);
int		exit_hook(t_vars *t);

#endif
