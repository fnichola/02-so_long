/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:16 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/17 23:20:42 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * Allocate memory and add one row to the map array. Also updates row count.
 */
static int	add_line_to_map(t_map *map, char *new_line)
{
	char **new_map;
	size_t	i;

	i = 0;
	map->rows += 1;
	new_map = (char **)malloc(sizeof(char *) * (map->rows + 1));
	// add error handling
	while (map->og_map[i])
	{
		new_map[i] = map->og_map[i];
		i++;
	}
	new_map[i] = new_line;
	new_map[i + 1] = NULL;
	free(map->og_map);
	map->og_map = new_map;
	return (0);
}

/**
 * Read from map file one line at a time and save in a 2D array.
 */
int	read_map_file(char *map_path, t_map *map)
{
	int		fd;
	char	*new_line;

	fd = open(map_path, O_RDONLY); // check for error!
	map->og_map = (char **)malloc(sizeof(char *));
	if (!map->og_map)
		end_game(); // need to return error message still
	map->og_map[0] = NULL;
	map->rows = 0;
	new_line = get_next_line(fd);
	// if (!new_line) error message!
	map->cols = ft_strlen(new_line) - 1;
	while (new_line)
	{
		add_line_to_map(map, new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
	return (0);
}


int	load_sprites(t_data *data)
{
	data->floor->dirt = mlx_xpm_file_to_image(data->mlx, "./assets/grass_dirt15.xpm", &(data->floor->width), &(data->floor->height));
	if (!data->floor->dirt)
	{
		printf("Failed to load sprite, exiting...\n");
		exit(EXIT_FAILURE);
	}
	
	data->wall->fence_0 = mlx_xpm_file_to_image(data->mlx, "./assets/fence_0.xpm", &(data->wall->width), &(data->wall->height));
	if (!data->wall->fence_0)
	{
		printf("Failed to load sprite, exiting...\n");
		exit(EXIT_FAILURE);
	}

	data->wall->fence_A = mlx_xpm_file_to_image(data->mlx, "./assets/fence_A.xpm", &(data->wall->width), &(data->wall->height));
	if (!data->wall->fence_A)
	{
		printf("Failed to load sprite, exiting...\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
