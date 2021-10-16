/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:25 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/16 20:35:06 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	draw_tiles(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <= (WIN_Y - TILE_SIZE))
	{
		x = 0;
		while (x <= (WIN_X - TILE_SIZE))
		{
			mlx_put_image_to_window(data->mlx, data->win, data->floor->dirt, x, y);
			x += TILE_SIZE;
		}
		y += TILE_SIZE;
	}

	x = 0;
	y = 0;
	while (y <= (WIN_Y - TILE_SIZE))
	{
		x = 0;
		while (x <= (WIN_X - TILE_SIZE))
		{
			mlx_put_image_to_window(data->mlx, data->win, data->wall->fence_0, x, y);
			x += WIN_X - TILE_SIZE;
		}
		y += TILE_SIZE;
	}
	return (0);
}
