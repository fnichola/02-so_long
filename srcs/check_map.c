/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:11:45 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/09 14:51:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_map_value(t_data *data, int r, int c)
{
	if (data->map.array[r][c] == PLAYER)
	{
		data->player.row = r;
		data->player.col = c;
		(data->player_count)++;
	}
	if (data->map.array[r][c] == COLLECTABLE)
		data->collectable.count++;
	if (data->map.array[r][c] == EXIT)
		(data->exit_count)++;
	if (!ft_strchr("01CPE", data->map.array[r][c]))
		end_game("Invalid character in map.");
	if (r == 0 || r == data->map.rows - 1 || c == 0
		|| c == data->map.cols - 1)
		if (data->map.array[r][c] != WALL)
			end_game("Map must be surrounded by walls.");
}

int	check_map(t_data *data)
{
	int	r;
	int	c;

	r = 0;
	c = 0;
	data->exit_count = 0;
	data->player_count = 0;
	data->collectable.count = 0;
	while (r < data->map.rows)
	{
		c = 0;
		while (c < data->map.cols)
		{
			check_map_value(data, r, c);
			c++;
		}
		r++;
	}
	if (data->exit_count < 1 || data->player_count != 1
		|| data->collectable.count < 1)
		end_game("Invalid map.");
	return (0);
}