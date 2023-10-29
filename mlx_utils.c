/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/29 21:57:18 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_cleanup(int returnCode, t_mlx *mlx)
{
	if (mlx->image)
		mlx_delete_image(mlx->win, mlx->image);
	if (mlx->win)
	{
		mlx_close_window(mlx->win);
		mlx_terminate(mlx->win);
	}
	if (returnCode)
		ft_putendl_fd(mlx_strerror(mlx_errno), 1);
	exit(returnCode);
}

int	ft_pixel(float r, float g, float b, float a)
{
	int	color;

	color = ((int)(ft_min_float(r, 1) * 0xff)) << 24;
	color |= ((int)(ft_min_float(g, 1) * 0xff)) << 16;
	color |= ((int)(ft_min_float(b, 1) * 0xff)) << 8;
	color |= (int)(ft_min_float(a, 1) * 0xff);
	return (color);
}

void	ft_pixel_iter(mlx_image_t *image, t_mlx *mlx,
			int (*f)(float, float, t_mlx *))
{
	int		color;
	t_uint	x;
	t_uint	y;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			color = (*f)(
					2 * (float)x / (float)image->width - 1,
					2 * (float)y / (float)image->width - 1,
					mlx);
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
