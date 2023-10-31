/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/31 19:10:04 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_julia(float x, float y, t_mlx *mlx)
{
	double	c[2];
	double	z[2];
	double	z2[2];
	double	distance;
	double	i;

	i = 0.0L;
	distance = 0.0L;
	c[0] = mlx->fract.z0[0];
	c[1] = mlx->fract.z0[1];
	z[0] = mlx->fract.center[0] + x * mlx->fract.ratio * mlx->fract.radius;
	z[1] = mlx->fract.center[1] + y * mlx->fract.radius;
	z2[0] = z[0] * z[0];
	z2[1] = z[1] * z[1];
	while (i < mlx->fract.iter && z2[0] + z2[1] < 4)
	{
		z[1] = 2 * z[0] * z[1] + c[1];
		z[0] = z2[0] - z2[1] + c[0];
		distance -= sqrt(z2[0] + z2[1]);
		z2[0] = z[0] * z[0];
		z2[1] = z[1] * z[1];
		distance += sqrt(z2[0] + z2[1]);
		i++;
	}
	return (ft_color(mlx, i, distance));
}
