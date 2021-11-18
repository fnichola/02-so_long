/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:16 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/18 18:14:09 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * Allocate memory and add one row to the map array. Also updates row count.
 */
static int	add_line_to_map(t_map *map, char *new_line)
{
	char	**new_map;
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

	check_map_file_ext(map_path);
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
