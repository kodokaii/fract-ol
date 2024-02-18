/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:09:23 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/10 19:10:11 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_move(t_mlx *mlx,
		double move_sensitivity, double mouse_sensitivity)
{
	static int	mouse_oldpos[2] = {0, 0};
	int			mouse_pos[2];

	if (mlx_is_mouse_down(mlx->win, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx->win, mouse_pos, mouse_pos + 1);
		mlx->fract.center[0] += (mouse_oldpos[0] - mouse_pos[0])
			* mouse_sensitivity;
		mlx->fract.center[1] += (mouse_oldpos[1] - mouse_pos[1])
			* mouse_sensitivity;
	}
	if (mlx_is_key_down(mlx->win, MLX_KEY_UP))
		mlx->fract.center[1] -= move_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_DOWN))
		mlx->fract.center[1] += move_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		mlx->fract.center[0] -= move_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		mlx->fract.center[0] += move_sensitivity;
	mlx_get_mouse_pos(mlx->win, mouse_oldpos, mouse_oldpos + 1);
}

static void	ft_modifier(t_mlx *mlx, double iter_sensitivity,
		double z0_sensitivity, double pow_sensitivity)
{
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		mlx->fract.z0[1] -= z0_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		mlx->fract.z0[1] += z0_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		mlx->fract.z0[0] -= z0_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		mlx->fract.z0[0] += z0_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_EQUAL))
		mlx->fract.iter += iter_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_MINUS)
		&& iter_sensitivity < mlx->fract.iter)
		mlx->fract.iter -= iter_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_E))
		mlx->fract.pow += pow_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_Q))
		mlx->fract.pow -= pow_sensitivity;
}

int	ft_color(t_mlx *mlx, double i, double length)
{
	double		bright;
	static int	colors[COLOR_COUNT][16] = {
	{0x000000FF, 0x050124FF, 0x090147FF, 0x040449FF, 0x000764FF, 0x0C2C8AFF,
		0x1852B1FF, 0x397DD1FF, 0x86B5E5FF, 0xD3ECF8FF, 0xF1E9BFFF, 0xF8C95FFF,
		0xFFAA00FF, 0xCC8000FF, 0x995700FF, 0x6A3403FF},
	{0xFFFFFFFF, 0xFFDBDBFF, 0xFFB6B6FF, 0xFF9292FF, 0xFF6D6DFF, 0xFF4949FF,
		0xFF2424FF, 0xFF0000FF, 0xDF0000FF, 0xBF0000FF, 0x9F0000FF, 0x800000FF,
		0x600000FF, 0x400000FF, 0x200000FF, 0x000000FF}};

	bright = i / mlx->fract.iter * length * 0.5L;
	if (mlx->fract.color == COLOR_COUNT)
		return (ft_pixel(bright, bright, bright, 1));
	if (i != mlx->fract.iter)
		bright = i / mlx->fract.iter;
	return (colors[mlx->fract.color][(t_uint)(bright * 67) % 16]);
}

void	ft_draw(void *param)
{
	t_mlx		*mlx;
	double		sensitivity;
	static int	(*f[FRACT_COUNT])(float, float, t_mlx *)
		= {&ft_mandelbrot, &ft_julia, &ft_burning_ship, &ft_multibrot};

	mlx = param;
	sensitivity = mlx->win->delta_time * mlx->fract.radius;
	ft_move(mlx, sensitivity * 0.15L, sensitivity * 0.05L);
	ft_modifier(mlx, 2.0L, sensitivity * 0.1L, 0.08L);
	ft_pixel_iter(mlx->image, mlx, f[mlx->fract.type]);
}
