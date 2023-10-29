/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/29 18:54:13 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_mandelbrot(float x, float y, t_mlx *mlx)
{
	double	c[2];
	double	z[2];
	double	z2[2];
	double	bright;
	t_uint	i;

	i = 0;
	c[0] = mlx->fract.center[0] + x * mlx->fract.ratio * mlx->fract.radius;
	c[1] = mlx->fract.center[1] + y * mlx->fract.radius;
	z[0] = mlx->fract.z0[0];
	z[1] = mlx->fract.z0[1];
	z2[0] = z[0] * z[0];
	z2[1] = z[1] * z[1];
	while (i <= mlx->fract.iter && z2[0] + z2[1] < 4)
	{
		z[1] = 2 * z[0] * z[1] + c[1];
		z[0] = z2[0] - z2[1] + c[0];
		z2[0] = z[0] * z[0];
		z2[1] = z[1] * z[1];
		i++;
	}
	if (mlx->fract.iter < i)
		return (0x000000ff);
	bright = (double)i / (double)mlx->fract.iter;
	return (ft_pixel(bright, bright, bright, 1));
}

void	ft_draw_mandelbrot(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	ft_pixel_iter(mlx->image, mlx, &ft_mandelbrot);
}
