#include <mlx.h>>
#include <stdio.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int loop_hook(void *win)
{
	int	x;
	int	y;
	
	mlx_mouse_get_pos(win, &x, &y);
	printf("%d, %d\n", x, y);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_loop_hook(vars.mlx, loop_hook, vars.win);
	mlx_loop(vars.mlx);
	return (0);
}
