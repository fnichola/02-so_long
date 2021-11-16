/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:25 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/16 03:45:35 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	put_image_to_frame_buf(t_data *data, void *img, int r, int c);
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

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

	/* mlx_put_image_to_window(data->mlx, data->win, data->floor, \
		c * TILE_SIZE, r * TILE_SIZE);*/
	put_image_to_frame_buf(data, data->floor, r, c);
	tile_img = find_tile_img(data, r, c);
	if (tile_img)
		put_image_to_frame_buf(data, tile_img, r, c);
		/* mlx_put_image_to_window(data->mlx, data->win, tile_img, \
			c * TILE_SIZE, r * TILE_SIZE);*/
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	addr = mlx_get_data_addr(data->frame_buf, &bits_per_pixel, &line_length, &endian);
	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	if (!(color & (0xFF << 24)))
		*(unsigned int*)dst = color;
}


static unsigned int	my_mlx_pixel_get(int x, int y, void *img)
{
	char	*src;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	src = addr + (y * line_length + x * (bits_per_pixel / 8));
	return (*(unsigned int*)src);
}

static void	put_image_to_frame_buf(t_data *data, void *img, int r, int c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			my_mlx_pixel_put(data, (c * TILE_SIZE) + x, (r * TILE_SIZE) + y, my_mlx_pixel_get(x, y, img));
			x++;
		}
		y++;
	}
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
	/* mlx_put_image_to_window(data->mlx, data->win, data->player.img, \
	 	c * TILE_SIZE, r * TILE_SIZE);*/
	put_image_to_frame_buf(data, data->player.img, r, c);
	mlx_put_image_to_window(data->mlx, data->win, data->frame_buf, 0, 0);
	return (0);
}
