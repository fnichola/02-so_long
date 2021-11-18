/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:15:37 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/18 21:43:15 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	init_game_vars(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		end_game("MLX initialization failed.");
	data->move_count = 0;
	data->walls = malloc(sizeof(void *) * 17);
	if (!data->walls)
		end_game("Error allocating memory for wall images.");
	data->walls[16] = NULL;
	data->map.array = malloc(sizeof(char *));
	if (!data->map.array)
		end_game("Error allocating memory for map array.");
	data->map.array[0] = NULL;
	data->map.rows = 0;
}

static void	init_game_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map.cols * TILE_SIZE, \
		data->map.rows * TILE_SIZE, "so_long");
	if (!data->win)
		end_game("MLX couldn't create a new window.");
	data->frame_buf = mlx_new_image(data->mlx, data->map.cols * TILE_SIZE, \
		data->map.rows * TILE_SIZE);
	data->addr = mlx_get_data_addr(data->frame_buf, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		end_game("Incorrect number of arguments.\n"\
		"Hint: Try './so_long maps/OK01_simple.ber'");
	init_game_vars(&data);
	read_map_file(argv[1], &(data.map));
	check_map(&data);
	load_sprites(&data);
	init_game_window(&data);
	render_screen(&data);
	setup_event_hooks(&data);
	mlx_loop(data.mlx);
	return (-1);
}
