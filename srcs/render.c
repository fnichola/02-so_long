/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:25 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/21 17:29:13 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*find_tile_img(t_data *data, int row, int col)
{
	t_map	*map;
	int		wall_type;

	wall_type = 0;
	map = data->map;

	if (map->og_map[row][col] == WALL)
		{
			if (row > 0)
				wall_type += (map->og_map[row - 1][col] == '1') * (1 << 3);
			if (col < (map->cols - 1))
				wall_type += (map->og_map[row][col + 1] == '1') * (1 << 2);
			if (row < (map->rows - 1))
				wall_type += (map->og_map[row + 1][col] == '1') * (1 << 1);
			if (col > 0)
				wall_type += (map->og_map[row][col - 1] == '1') * 1;
			return (data->walls[wall_type]);
		}
	else if (map->og_map[row][col] == COLLECTABLE)
		return (data->collectable.img);
	else if (map->og_map[row][col] == EXIT)
		return (data->exit_img);
	return (NULL);
}

int	draw_tiles(t_data *data)
{
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
	c = data->player.col;
	r = data->player.row;
	mlx_put_image_to_window(data->mlx, data->win, data->player.img, c * TILE_SIZE, r * TILE_SIZE);
	return (0);
}
