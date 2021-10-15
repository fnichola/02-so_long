/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:50:34 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/15 19:26:56 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

#define	WIN_X	320
#define	WIN_Y	320
#define	TILE_SIZE	32

typedef enum e_tiletype
{
	EMPTY = '0',
	WALL = '1',
	COLLECTABLE = 'C',
	PLAYER = 'P',
	EXIT = 'E',
}	t_tiletype;

/* Struct for each tile */
typedef struct s_tile
{
	t_tiletype		type;
	t_tiletype		og_type;
	void			*img;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
}					t_tile;

typedef struct	s_rgb
{
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
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_data *data)
{
	printf("key_hook: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 13) // W
		data->player.y -= 50;
	if (keycode == 0) // A
		data->player.x -=50;
	if (keycode == 1) // S
		data->player.y += 50;
	if (keycode == 2) // D
		data->player.x +=50;
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->player.x, data->player.y);
	return (0);
}


int	close()
{
	exit(EXIT_SUCCESS);
}

int	make_image(t_data *data)
{
	int		x;
	int		y;
	unsigned int	color;

	color = 0x0000FF00;
	x = 0;
	y = 0;
	while (y < 50)
	{
		x = 0;
		while (x < 50)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}

int	load_sprites(t_data *data)
{
	data->floor->dirt = mlx_xpm_file_to_image(data->mlx, "./assets/grass_dirt15.xpm", &(data->floor->width), &(data->floor->height));
	if (!data->floor->dirt)
	{
		printf("Failed to load sprite, exiting...\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	draw_tiles(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < (WIN_Y - TILE_SIZE))
	{
		x = 0;
		while (x < (WIN_X - TILE_SIZE))
		{
			mlx_put_image_to_window(data->mlx, data->win, data->floor->dirt, x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	return (0);
}

int	main(void)
{
	t_data		data;
	t_floor_img	floor;

	data.floor = &floor; 

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_X, WIN_Y, "Hello world!");
	// data.color.red = 0;
	// data.color.green = 0;
	// data.color.blue = 0;
	// data.player.x = 0;
	// data.player.y = 0;
	// data.img = mlx_new_image(data.mlx, 50, 50);
	// data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
	// 							&data.endian);
	// make_image(&data);
	// // mlx_key_hook(data.win, key_hook, &data);
	// mlx_hook(data.win, 17, (1L<<17), close, &data);
	// // mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	//load_sprites(&data);
	int width = 0;
	int height = 0;
	void *img;
	char *path = "./assets/grass_dirt15_2.xpm";
	img = mlx_xpm_file_to_image(data.mlx, path, &width, &height);
	// draw_tiles(&data);
	mlx_loop(data.mlx);
	return (0);
}
