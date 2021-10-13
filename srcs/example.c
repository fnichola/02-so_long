/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:50:34 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/13 22:15:18 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

#define	WIN_X	250
#define	WIN_Y	250

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_rgb
{
	long	red;
	long	green;
	long	blue;
}				t_rgb;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_vars	*vars;
	t_rgb	color;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;

	printf("key_hook: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	(void)vars;

	printf("mouse_hook: (%d) %d, %d\n", button, x, y);
	return (0);
}

int	close()
{
	exit(EXIT_SUCCESS);
}

int	render_next_frame(t_data *data)
{
	int		x;
	int		y;
	long	color;

	if (data->color.red < 0xff && data->color.green == 0 && data->color.blue == 0)
		data->color.red += 1;
	else if (data->color.green < 0xff && data->color.blue == 0)
		{
			data->color.red -= 1;
			data->color.green += 1;
		}
	else if (data->color.blue < 0xff)
		{
			data->color.green -= 1;
			data->color.blue += 1;
		}
	else
		data->color.blue = 0;
	
	color = (data->color.red<<16) + (data->color.green<<8) + (data->color.blue);


	x = 0;
	y = 0;
	while (y <= WIN_Y)
	{
		x = 0;
		while (x <= WIN_X)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->vars->mlx, data->vars->win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	data;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_X, WIN_Y, "Hello world!");
	data.color.red = 0;
	data.color.green = 0;
	data.color.blue = 0;
	data.vars = &vars;
	data.img = mlx_new_image(vars.mlx, WIN_X, WIN_Y);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 17, (1L<<17), close, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &data);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
