/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:15:37 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/21 22:32:18 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(void)
{
	t_data		data;
	t_floor_img	floor;
	t_map		map;

	data.map = &map;
	data.floor = &floor; 
	data.walls = (void **)malloc(sizeof(void *) * 17);
	data.walls[16] = NULL;
	data.collectable.count = 0;

	read_map_file("map.ber", &map);
	check_map(&data);

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, map.cols * TILE_SIZE, map.rows * TILE_SIZE, "so_long");
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, (1L<<17), end_game, &data);
	load_sprites(&data);
	draw_tiles(&data);
	mlx_loop(data.mlx);
}
