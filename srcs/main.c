/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:15:37 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/26 18:20:43 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void init_game_vars(t_data *data)
{
	data->move_count = 0;
	data->walls = malloc(sizeof(void *) * 17);
	if (!data->walls)
		end_game("Error allocationg memory for wall images.");
	data->walls[16] = NULL;
	data->map.array = malloc(sizeof(char *));
	if (!data->map.array)
		end_game("Error allocating memory for map array.");
	data->map.array[0] = NULL;
	data->map.rows = 0;
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		end_game("Incorrect number of arguments."); 
	data.mlx = mlx_init();
	if (!data.mlx)
		end_game("MLX initialization failed.");
	init_game_vars(&data);
	read_map_file(argv[1], &(data.map));
	check_map(&data);
	load_sprites(&data);
	data.win = mlx_new_window(data.mlx, data.map.cols * TILE_SIZE, data.map.rows * TILE_SIZE, "so_long");
	if (!data.win)
		end_game("MLX couldn't create a new window.");
	render_screen(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, (1L<<17), end_game, &data);
	mlx_loop(data.mlx);
}
