/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:08:27 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/18 20:52:26 by fnichola         ###   ########.fr       */
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

# define WIN_X	640
# define WIN_Y	640
# define TILE_SIZE	32
# define HEX_UPPER	"0123456789ABCDEF"

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

typedef struct s_collectable {
	void	*img;
	int		count;
}				t_collectable;

typedef struct s_player
{
	void	*img;
	int		row;
	int		col;
}				t_player;

typedef struct s_data {
	void			*mlx;
	void			*win;
	char			*addr;
	void			*frame_buf;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_player		player;
	void			*floor;
	void			**walls;
	t_collectable	collectable;
	void			*exit_img;
	int				move_count;
	int				exit_count;
	int				player_count;
	t_map			map;
}				t_data;

int				read_map_file(char *map_path, t_map *map);
int				check_map(t_data *data);
int				check_map_file_ext(char *map_path);
int				check_map_line_length(char *new_line, int expected_length);
int				load_sprites(t_data *data);
void			setup_event_hooks(t_data *data);
int				key_hook(int keycode, t_data *data);
void			*find_tile_img(t_data *data, int row, int col);
unsigned int	get_pixel_from_img(int x, int y, void *img);
void			put_pixel_to_frame_buf(t_data *data, int x, int y, int color);
int				render_screen(t_data *data);
int				end_game(char *error_message);

#endif
