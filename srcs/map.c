/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:16 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/26 17:57:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map(t_data *data)
{
	int r;
	int c;
	int	exit_count;
	int	player_count;

	r = 0;
	c = 0;
	exit_count = 0;
	player_count = 0;
	data->collectable.count = 0;
	while (r < data->map.rows)
	{
		c = 0;
		while (c < data->map.cols)
		{
			if (data->map.array[r][c] == PLAYER)
			{
				data->player.row = r;
				data->player.col = c;
				player_count++;
			}
			if (data->map.array[r][c] == COLLECTABLE)
				data->collectable.count++;
			if (data->map.array[r][c] == EXIT)
				exit_count++;
			if (!ft_strchr("01CPE", data->map.array[r][c]))
				end_game("Invalid character in map.");
			c++;
		}
		r++;
	}
	if (exit_count < 1 || player_count != 1 || data->collectable.count < 1)
		end_game("Invalid map.");
	return (0);
}

int	check_map_line_length(char *new_line, int expected_length)
{
	int	new_line_length;

	new_line_length = ft_strlen(new_line);
	if (ft_strchr(new_line, '\n'))
		new_line_length -= 1;
	return (new_line_length == expected_length);
}

/**
 * Allocate memory and add one row to the map array. Also updates row count.
 */
static int	add_line_to_map(t_map *map, char *new_line)
{
	char **new_map;
	size_t	i;

	i = 0;
	map->rows += 1;
	new_map = malloc(sizeof(char *) * (map->rows + 1));
	if (!new_map)
		end_game("Error allocating memory for new_map.");
	while (map->array[i])
	{
		new_map[i] = map->array[i];
		i++;
	}
	new_map[i] = new_line;
	new_map[i + 1] = NULL;
	free(map->array);
	map->array = new_map;
	return (0);
}

/** 
 * Read from map file one line at a time and save in a 2D array.
 */
int	read_map_file(char *map_path, t_map *map)
{
	int		fd;
	char	*new_line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		end_game("Couldn't open map file.");
	new_line = get_next_line(fd);
	if (!new_line)
		end_game("Failed to read from map file.");
	map->cols = ft_strlen(new_line) - 1;
	while (new_line)
	{
		if (!check_map_line_length(new_line, map->cols))
			end_game("Map is not rectangular.");
		add_line_to_map(map, new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
	return (0);
}


int	load_sprites(t_data *data)
{
	int	i;
	char	*hex;
	char	*file_path;
	int		width;
	int		height;
	
	hex = ft_strdup(HEX_UPPER);
	
	data->floor = mlx_xpm_file_to_image(data->mlx, "./assets/grass_dirt15.xpm", &width, &height);
	if (!data->floor)
	{
		ft_printf("Failed to load sprite, exiting...\n");
		exit(EXIT_FAILURE);
	}
	file_path = ft_strdup("./assets/fence_0.xpm");
	i = 0;
	while (i < 16)
	{
		file_path[15] = hex[i];
		data->walls[i] = mlx_xpm_file_to_image(data->mlx, file_path, &width, &height);
		if (!data->walls[i])
		{
			ft_printf("Failed to load sprite, exiting...\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	data->player.img = mlx_xpm_file_to_image(data->mlx, "./assets/cat001.xpm", &width, &height);
	if (!data->player.img)
	{
		ft_printf("Failed to load character sprite, exiting...\n");
		exit(EXIT_FAILURE);
	}
	data->collectable.img = mlx_xpm_file_to_image(data->mlx, "./assets/apples.xpm", &width, &height);
	if (!data->collectable.img)
	{
		ft_printf("Failed to load collectable sprite, exiting...\n");
	}
	data->exit_img = mlx_xpm_file_to_image(data->mlx, "./assets/stairs.xpm", &width, &height);
	if (!data->player.img)
	{
		ft_printf("Failed to load exit sprite, exiting...\n");
	}
	free(hex);
	free(file_path);
	return (0);



}
