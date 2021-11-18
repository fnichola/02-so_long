/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:09:04 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/18 20:50:35 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	put_pixel_to_frame_buf(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_from_img(int x, int y, void *img)
{
	char	*src;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	src = addr + (y * line_length + x * (bits_per_pixel / 8));
	return (*(unsigned int *)src);
}
