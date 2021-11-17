/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:17:22 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/17 08:25:27 by fnichola         ###   ########.fr       */
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
