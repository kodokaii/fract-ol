/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/02 17:31:34 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_resize_hook(int width, int heigth, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx->fract.ratio = (double)width / (double)heigth;
	mlx_resize_image(mlx->image, width, heigth);
}

void	ft_scroll_hook(double xdelta, double ydelta, void *param)
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

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_cleanup(0, mlx);
	if (keydata.key == MLX_KEY_1)
		mlx->fract.color = COLOR_COUNT;
	if (keydata.key == MLX_KEY_2)
		mlx->fract.color = 0;
	if (keydata.key == MLX_KEY_3)
		mlx->fract.color = 1;
}
