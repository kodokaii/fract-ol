/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:22:49 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/31 19:13:46 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_resize(int width, int heigth, void *param)
{
	t_mlx	*mlx;	

	mlx = param;
	mlx->fract.ratio = (double)width / (double)heigth;
	mlx_resize_image(mlx->image, width, heigth);
}

void	ft_zoom(double xdelta, double ydelta, void *param)
{
	int		mouse_pos[2];
	double	iter_sensitivity;
	double	scroll_sensitivity;
	double	mousse_sensitivity;
	t_mlx	*mlx;	

	(void)xdelta;
	mlx = param;
	mlx_get_mouse_pos(mlx->win, mouse_pos, mouse_pos + 1);
	mousse_sensitivity = mlx->fract.radius * 0.2L;
	scroll_sensitivity = mlx->fract.radius * 0.1L;
	iter_sensitivity = 2;
	mlx->fract.iter += ydelta * iter_sensitivity;
	mlx->fract.radius -= ydelta * scroll_sensitivity;
	mlx->fract.center[0] += mousse_sensitivity * mlx->fract.ratio
		* ((double)mouse_pos[0] / (double)mlx->win->width - 0.5);
	mlx->fract.center[1] += mousse_sensitivity
		* ((double)mouse_pos[1] / (double)mlx->win->height - 0.5);
}

void	ft_move(t_mlx *mlx, double sensitivity)
{
	static int	mouse_oldpos[2] = {-1, -1};
	int			mouse_pos[2];

	if (mlx_is_mouse_down(mlx->win, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx->win, mouse_pos, mouse_pos + 1);
		mlx->fract.center[0] += (mouse_oldpos[0] - mouse_pos[0])
			* sensitivity * 0.5L;
		mlx->fract.center[1] += (mouse_oldpos[1] - mouse_pos[1])
			* sensitivity * 0.5L;
	}
	if (mlx_is_key_down(mlx->win, MLX_KEY_UP))
		mlx->fract.center[1] -= sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_DOWN))
		mlx->fract.center[1] += sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		mlx->fract.center[0] -= sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		mlx->fract.center[0] += sensitivity;
	mlx_get_mouse_pos(mlx->win, mouse_oldpos, mouse_oldpos + 1);
}

int	ft_color(t_mlx *mlx, double i, double distance)
{
	double		bright;
	static int	color[] = {0x42300FFF, 0x19071AFF, 0x090147FF, 0x040449FF,
		0x000764FF, 0x0C2C8AFF, 0x1852B1FF, 0x397DD1FF,
		0x86B5E5FF, 0xD3ECF8FF, 0xF1E9BFFF, 0xF8C95FFF,
		0xFFAA00FF, 0xCC8000FF, 0x995700FF, 0x6A3403FF};

	if (mlx->fract.color == 0)
	{
		bright = i / mlx->fract.iter * fabs(distance) * 0.5L;
		return (ft_pixel(bright, bright, bright, 1));
	}
	if (i == mlx->fract.iter)
		bright = fabs(distance) * 0.5L;
	else
		bright = i / mlx->fract.iter;
	return (color[(t_uint)(bright * 67) % 16]);
}

void	ft_draw(void *param)
{
	t_mlx		*mlx;
	double		iter_sensitivity;
	double		move_sensitivity;
	static int	(*f[FRACT_COUNT])(float, float, t_mlx *)
		= {&ft_mandelbrot, &ft_julia};

	mlx = param;
	iter_sensitivity = 2.0L;
	move_sensitivity = mlx->win->delta_time * mlx->fract.radius * 0.1L;
	ft_move(mlx, move_sensitivity);
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		mlx->fract.z0[1] -= move_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		mlx->fract.z0[1] += move_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		mlx->fract.z0[0] -= move_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		mlx->fract.z0[0] += move_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_EQUAL))
		mlx->fract.iter += iter_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_MINUS)
		&& iter_sensitivity < mlx->fract.iter)
		mlx->fract.iter -= iter_sensitivity;
	ft_pixel_iter(mlx->image, mlx, f[mlx->fract.type]);
}
