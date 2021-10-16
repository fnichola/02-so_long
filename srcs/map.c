/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:16 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/16 20:34:09 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
