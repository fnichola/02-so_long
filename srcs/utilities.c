/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:22 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/22 00:00:34 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	end_game()
{
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 13) // W
		if (data->map->og_map[data->player.row - 1][data->player.col] != WALL)
			data->player.row -= 1;
	if (keycode == 0) // A
		if (data->map->og_map[data->player.row][data->player.col - 1] != WALL)
			data->player.col -= 1;
	if (keycode == 1) // S
		if (data->map->og_map[data->player.row + 1][data->player.col] != WALL)
			data->player.row += 1;
	if (keycode == 2) // D
		if (data->map->og_map[data->player.row][data->player.col + 1] != WALL)
			data->player.col += 1;
	mlx_clear_window(data->mlx, data->win);
	draw_tiles(data);
	return (0);
}
