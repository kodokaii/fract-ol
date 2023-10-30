/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:22:49 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/30 04:26:17 by nlaerema         ###   ########.fr       */
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
	int		mousse_pos[2];
	double	scroll_sensitivity;
	double	mousse_sensitivity;
	t_mlx	*mlx;	

	(void)xdelta;
	mlx = param;
	mlx_get_mouse_pos(mlx->win, mousse_pos, mousse_pos + 1);
	scroll_sensitivity = mlx->win->delta_time * mlx->fract.radius;
	mousse_sensitivity = mlx->win->delta_time * mlx->fract.radius * 2;
	mlx->fract.radius -= ydelta * scroll_sensitivity;
	mlx->fract.center[0] += mousse_sensitivity * mlx->fract.ratio
		* ((double)mousse_pos[0] / (double)mlx->win->width - 0.5);
	mlx->fract.center[1] += mousse_sensitivity
		* ((double)mousse_pos[1] / (double)mlx->win->height - 0.5);
}

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_cleanup(0, param);
}

void	ft_move(t_mlx *mlx, double sensitivity)
{
	if (mlx_is_key_down(mlx->win, MLX_KEY_UP))
		mlx->fract.center[1] -= sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_DOWN))
		mlx->fract.center[1] += sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT))
		mlx->fract.center[0] -= sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_RIGHT))
		mlx->fract.center[0] += sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		mlx->fract.z0[1] -= sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		mlx->fract.z0[1] += sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		mlx->fract.z0[0] -= sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		mlx->fract.z0[0] += sensitivity;
}

void	ft_draw(void *param)
{
	t_mlx		*mlx;
	float		iter_sensitivity;
	double		move_sensitivity;
	static int	(*f[FRACT_COUNT])(float, float, t_mlx *)
		= {&ft_mandelbrot};

	mlx = param;
	iter_sensitivity = (float)mlx->fract.iter * mlx->win->delta_time * 0.5;
	iter_sensitivity = ft_max_float(iter_sensitivity, 1);
	move_sensitivity = mlx->win->delta_time * mlx->fract.radius;
	ft_move(mlx, move_sensitivity);
	if (mlx_is_key_down(mlx->win, MLX_KEY_EQUAL))
		mlx->fract.iter += iter_sensitivity;
	if (mlx_is_key_down(mlx->win, MLX_KEY_MINUS)
		&& iter_sensitivity < mlx->fract.iter)
		mlx->fract.iter -= iter_sensitivity;
	ft_pixel_iter(mlx->image, mlx, f[mlx->fract.type]);
}
