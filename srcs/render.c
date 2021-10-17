/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:25 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/17 23:22:46 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*find_tile_img(t_data *data, int row, int col)
{
	char	**map;

	map = data->map->og_map;

	if ((map[row])[col] == '1')
		return (data->wall->fence_0);
	else
		return (NULL);
}

int	draw_tiles(t_data *data)
{
	int	x;
	int	y;
	int	r;
	int	c;
	void	*tile_img;

	r = 0;
	c = 0;
	while (r < data->map->rows)
	{
		c = 0;
		while (c < data->map->cols)
		{
			
			mlx_put_image_to_window(data->mlx, data->win, data->floor->dirt, c * TILE_SIZE, r * TILE_SIZE);
			tile_img = find_tile_img(data, r, c);
			if (tile_img)
				mlx_put_image_to_window(data->mlx, data->win, tile_img, c * TILE_SIZE, r * TILE_SIZE);
			c++;
		}
		r++;
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
