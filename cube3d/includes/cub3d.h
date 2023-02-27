/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuntini <dzuntini@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:53:08 by jrathelo          #+#    #+#             */
/*   Updated: 2022/04/21 12:41:15 by dzuntini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Screen
# ifndef SWID
#  define SWID 960
# endif

# ifndef SHGHT
#  define SHGHT 540
# endif

// KEY CODES
# define ESCAPE		53
# define U_ARROW	126
# define D_ARROW	125
# define L_ARROW	123
# define R_ARROW	124
# define W			13
# define A			0
# define S			1
# define D			2

// COLOR CODES
# define RED 	0x00FF0000
# define GREEN 	0x0000FF00
# define BLUE 	0x000000FF
# define CYAN	0x0000FFFF
# define PURPLE 0x00FF00FF
# define WHITE 	0x00FFFFFF
# define BLACK 	0x00000000
# define YELLOW 0x00FFFF00

//testing
# define MAPHIGHT 24
# define MAPWIDTH 24

# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <libft.h>
# include <string.h>
# include <get_next_line.h>

// Utility
typedef struct s_cords{
	double	x;
	double	y;
}				t_cords;

typedef struct s_cordsi{
	int	x;
	int	y;
}				t_cordsi;

typedef struct s_img_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		textheight;
	int		textwidth;
}				t_img_data;

typedef struct s_fflags {
	bool	xntext;
	bool	xstext;
	bool	xetext;
	bool	xwtext;
	bool	sky;
	bool	floor;

	bool	sf;
	bool	text_tab;
	bool	map;
	bool	parsed;
}	t_free;

typedef struct s_mini
{
	t_cordsi	minicasecoord;
	t_cordsi	oldnav;
}			t_mm;

typedef struct s_data {
	int			sky[3];
	int			floor[3];
	char		dir;

	t_img_data	xntext;
	t_img_data	xstext;
	t_img_data	xetext;
	t_img_data	xwtext;

	char		**map;
	char		**parsed;
	char		**text_tab;
	char		**sf;
	size_t		mwidth;
	size_t		mheight;
}			t_data;

typedef struct s_raycords {
	t_cords		dir;
	t_cords		plane;
	t_cordsi	mappos;
	t_cords		pos;
	t_cords		sidedist;
	t_cords		deltadist;
	t_cords		raydir;
	t_cords		step;
}				t_raycords;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_img_data	img;
	t_free		fflags;
	t_data		data;
	t_mm		mm;
	t_raycords	corddata;
	double		r;
}				t_cub;

typedef struct s_raycast_line {
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		side;
	double	wallpos;
}				t_raycasy_line;

void	ft_freeandexit(t_cub *cub, int code);

// Initilization
void	cub_map_init(char *path, t_cub *cub);
int		param_parse(const char *str, t_cub *cub);
int		check_begin(const char *s, const char *b);
void	final_check(t_cub *cub);
void	init_textures(t_cub *cub);
void	check_closed_walls(t_cub *cub);
char	*ft_read_loop(int bytesred, char buff[2], int fd);
void	skyndfloor(char c, t_cub *cub);
void	n_put(t_cub *cub, char *str);
void	s_put(t_cub *cub, char *str);
void	e_put(t_cub *cub, char *str);
void	w_put(t_cub *cub, char *str);

// Raycasting
t_cords	cub_get_facing_cordinates(double r);
void	tester_raycast(t_cub *cub);

// minilibx
int		cub_close_prog(t_cub *vars);
int		cub_key_press(int keycode, t_cub *vars);
void	cub_main_loop(t_cub *cub);
void	cub_move_arround(int keycode, t_cub *vars);
void	cub_strafe_right(t_cub *vars);
void	cub_strafe_left(t_cub *vars);
void	minimap(t_cub *cub);

// minilibx drawing tools
void	draw_pixel(t_img_data *d, t_cordsi c, int color);
void	draw_raycast_line(t_cub *cub, t_raycasy_line line, int x);
void	raycast(t_cub *cub);

//util
int		main(int ac, char **av);
int		check_letter(char c, char *base);
int		check_letter_line(char *str, char *base);
void	ft_errfreeandexit(char *str, t_cub *cub, int code);
void	ft_freeandexit(t_cub *cub, int code);
int		check_tabsize(char **tab, int size);
int		ft_atoi2(const char *str);
void	freestuff(char c, t_cub *cub);
void	var_set_direction2(t_cub *cub, int dir);
void	replace_letter(t_cub *cub, char torep, char with);

#endif