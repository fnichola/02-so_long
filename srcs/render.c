/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:25 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/09 16:44:32 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*find_tile_img(t_data *data, int row, int col)
{
	int		wall_type;

	wall_type = 0;
	if (data->map.array[row][col] == WALL)
	{
		if (row > 0)
			wall_type += (data->map.array[row - 1][col] == '1') * (1 << 3);
		if (col < (data->map.cols - 1))
			wall_type += (data->map.array[row][col + 1] == '1') * (1 << 2);
		if (row < (data->map.rows - 1))
			wall_type += (data->map.array[row + 1][col] == '1') * (1 << 1);
		if (col > 0)
			wall_type += (data->map.array[row][col - 1] == '1') * 1;
		return (data->walls[wall_type]);
	}
	else if (data->map.array[row][col] == COLLECTABLE)
		return (data->collectable.img);
	else if (data->map.array[row][col] == EXIT)
		return (data->exit_img);
	return (NULL);
}

static void put_images(t_data *data, )

int	render_screen(t_data *data)
{
	int		r;
	int		c;
	void	*tile_img;

	r = 0;
	c = 0;
	while (r < data->map.rows)
	{
		c = 0;
		while (c < data->map.cols)
		{
			mlx_put_image_to_window(data->mlx, data->win, data->floor, \
				c * TILE_SIZE, r * TILE_SIZE);
			tile_img = find_tile_img(data, r, c);
			if (tile_img)
				mlx_put_image_to_window(data->mlx, data->win, tile_img, \
					c * TILE_SIZE, r * TILE_SIZE);
			c++;
		}
		r++;
	}
	c = data->player.col;
	r = data->player.row;
	mlx_put_image_to_window(data->mlx, data->win, data->player.img, \
		c * TILE_SIZE, r * TILE_SIZE);
	return (0);
}
