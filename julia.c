/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/02 16:19:32 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_julia_iter(double z[2], double z2[2], double c[2])
{
	z[1] = 2 * z[0] * z[1] + c[1];
	z[0] = z2[0] - z2[1] + c[0];
	z2[0] = z[0] * z[0];
	z2[1] = z[1] * z[1];
}

int	ft_julia(float x, float y, t_mlx *mlx)
{
	double	c[2];
	double	z[2];
	double	z2[2];
	double	length;
	double	i;

	i = 0.0L;
	c[0] = mlx->fract.z0[0];
	c[1] = mlx->fract.z0[1];
	z[0] = mlx->fract.center[0] + x * mlx->fract.ratio * mlx->fract.radius;
	z[1] = mlx->fract.center[1] + y * mlx->fract.radius;
	z2[0] = z[0] * z[0];
	z2[1] = z[1] * z[1];
	length = sqrt(z2[0] + z2[1]);
	while (i < mlx->fract.iter && z2[0] + z2[1] < 4)
	{
		ft_julia_iter(z, z2, c);
		i++;
	}
	length = ft_abs_double(sqrt(z2[0] + z2[1]) - length);
	return (ft_color(mlx, i, length));
}
