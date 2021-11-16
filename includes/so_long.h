/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:08:27 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/16 21:57:23 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "../mlx-linux/mlx.h"

# define	WIN_X	640
# define	WIN_Y	640
# define	TILE_SIZE	32
# define	HEX_UPPER	"0123456789ABCDEF"

typedef enum e_tiletype {
	EMPTY = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
}				t_tiletype;


# ifdef LINUX
typedef enum e_keycode {
	UP = 119,
	DOWN = 115,
	LEFT = 97,
	RIGHT = 100,
	ESC = 65307,
}				t_keycode;
# else
typedef enum e_keycode {
	UP = 13,
	DOWN = 1,
	LEFT = 0,
	RIGHT = 2,
	ESC = 53,
}				t_keycode;
# endif

typedef struct s_map {
	char	**array;
	int		rows;
	int		cols;
}				t_map;

typedef struct s_tile {
	t_tiletype		type;
	t_tiletype		og_type;
	void			*img;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
}				t_tile;

typedef struct s_rgb {
	long	red;
	long	green;
	long	blue;
}				t_rgb;

typedef struct s_player
{
	void	*img;
	int		row;
	int		col;
}				t_player;

typedef struct s_collectable {
	void	*img;
	int		count;
}				t_collectable;

typedef struct s_data {
	void			*mlx;
	void			*win;
	char			*addr;
	void			*frame_buf;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_rgb			color;
	t_player		player;
	void			*floor;
	void			**walls;
	t_collectable	collectable;
	void			*exit_img;
	int				move_count;
	t_map			map;
	int				exit_count;
	int				player_count;
}				t_data;

//void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		load_sprites(t_data *data);
int		key_hook(int keycode, t_data *data);
int		render_screen(t_data *data);
int		read_map_file(char *map_path, t_map *map);
void	*find_tile_img(t_data *data, int row, int col);
int		check_map(t_data *data);
int		end_game(char *error_message);

#endif
