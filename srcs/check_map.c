/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:11:45 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/18 18:12:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_line_length(char *new_line, int expected_length)
{
	int	new_line_length;

	new_line_length = ft_strlen(new_line);
	if (ft_strchr(new_line, '\n'))
		new_line_length -= 1;
	return (new_line_length == expected_length);
}

int	check_map_file_ext(char *map_path)
{
	size_t	path_length;
	char	*ber;

	path_length = ft_strlen(map_path);
	ber = ft_strnstr(map_path, ".ber", path_length);
	if (ber)
	{
		if (ber == (map_path + path_length - 4))
			return (1);
	}
	end_game("Invalid map file extension. Must be '.ber'");
	return (0);
}

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
