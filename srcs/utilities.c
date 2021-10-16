/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:22 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/16 20:35:41 by fnichola         ###   ########.fr       */
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
		data->player.y -= 50;
	if (keycode == 0) // A
		data->player.x -=50;
	if (keycode == 1) // S
		data->player.y += 50;
	if (keycode == 2) // D
		data->player.x +=50;
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img, data->player.x, data->player.y);
	return (0);
}
