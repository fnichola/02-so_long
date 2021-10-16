/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:08:27 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/16 21:48:12 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

# define	WIN_X	640
# define	WIN_Y	640
# define	TILE_SIZE	32
# define	HEX_UPPER	"01234567890ABCDEF"

typedef enum	e_tiletype {
	EMPTY = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
}				t_tiletype;

typedef struct	s_map {
	char	**og_map;
	int		rows;
	int		cols;
}				t_map;


typedef struct	s_tile {
	t_tiletype		type;
	t_tiletype		og_type;
	void			*img;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
}				t_tile;

typedef struct	s_rgb {
	long	red;
	long	green;
	long	blue;
}				t_rgb;

typedef struct	s_player
{
	int	x;
	int	y;
}				t_player;

typedef struct	s_floor_img {
	void	*dirt;
	int		width;
	int		height;
}				t_floor_img;

typedef struct	s_wall_img {
	void	*fence_0;
	void	*fence_A;
	int		width;
	int		height;
}				t_wall_img;

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_rgb	color;
	t_player	player;
	t_floor_img	*floor;
	t_wall_img	*wall;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	load_sprites(t_data *data);
int	end_game();
int	key_hook(int keycode, t_data *data);
int	draw_tiles(t_data *data);
int	read_map_file(char *map_path);

#endif

