/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:25 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/18 20:50:37 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	put_image_to_frame_buf(t_data *data, void *img, int r, int c)
{
	int	x;
	int	y;
	int	pixel;

	x = 0;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			pixel = get_pixel_from_img(x, y, img);
			if (!(pixel & (0xFF << 24)))
				put_pixel_to_frame_buf(data, (c * TILE_SIZE) + x, \
					(r * TILE_SIZE) + y, pixel);
			x++;
		}
		y++;
	}
}

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

static void	put_images(t_data *data, int r, int c)
{
	void	*tile_img;

	put_image_to_frame_buf(data, data->floor, r, c);
	tile_img = find_tile_img(data, r, c);
	if (tile_img)
		put_image_to_frame_buf(data, tile_img, r, c);
}

int	render_screen(t_data *data)
{
	int		r;
	int		c;

	r = 0;
	c = 0;
	while (r < data->map.rows)
	{
		c = 0;
		while (c < data->map.cols)
		{
			put_images(data, r, c);
			c++;
		}
		r++;
	}
	c = data->player.col;
	r = data->player.row;
	put_image_to_frame_buf(data, data->player.img, r, c);
	mlx_put_image_to_window(data->mlx, data->win, data->frame_buf, 0, 0);
	return (0);
}
