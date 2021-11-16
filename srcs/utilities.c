/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:22 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/16 01:46:50 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	end_game(char *error_message)
{
	if (error_message)
	{
		ft_printf_fd(STDERR_FILENO, "Error\n%s\n", error_message);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_SUCCESS);
}

int	check_action(t_data *data, int row, int col)
{
	if (data->map.array[row][col] != WALL)
	{
		if (data->map.array[row][col] == COLLECTABLE)
		{
			data->collectable.count--;
			data->map.array[row][col] = EMPTY;
		}
		if (data->map.array[row][col] == EXIT)
		{
			if (data->collectable.count == 0)
			{
				ft_printf("Moves: %d\nYou won!\n", ++data->move_count);
				end_game(NULL);
			}
		}
		ft_printf("Moves: %d\n", ++data->move_count);
		return (1);
	}
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(EXIT_SUCCESS);
	}
	if (keycode == UP) //up
		if (check_action(data, data->player.row - 1, data->player.col))
			data->player.row -= 1;
	if (keycode == LEFT) //left
		if (check_action(data, data->player.row, data->player.col - 1))
			data->player.col -= 1;
	if (keycode == DOWN) //down
		if (check_action(data, data->player.row + 1, data->player.col))
			data->player.row += 1;
	if (keycode == RIGHT) //right
		if (check_action(data, data->player.row, data->player.col + 1))
			data->player.col += 1;
	mlx_clear_window(data->mlx, data->win);
	render_screen(data);
	return (0);
}
