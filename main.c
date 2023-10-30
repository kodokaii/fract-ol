/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:22:49 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/30 21:10:28 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_cleanup(0, mlx);
	if (keydata.key == MLX_KEY_1)
		mlx->fract.color = 0;
	if (keydata.key == MLX_KEY_2)
		mlx->fract.color = 1;
}

int	ft_mlx_init(t_mlx *mlx, char c)
{
	mlx->win = NULL;
	mlx->image = NULL;
	mlx->fract.center[0] = 0.0L;
	mlx->fract.center[1] = 0.0L;
	mlx->fract.z0[0] = 0.0L;
	mlx->fract.z0[1] = 0.0L;
	mlx->fract.radius = 2.0L;
	mlx->fract.iter = 21.0L;
	mlx->fract.type = ft_strchr(VALID_ARG, c) - VALID_ARG;
	mlx->fract.color = 0;
	mlx->win = mlx_init(FT_WIDTH, FT_HEIGHT, "fractol", true);
	if (!mlx->win)
		return (1);
	mlx->image = mlx_new_image(mlx->win, FT_WIDTH, FT_HEIGHT);
	if (!mlx->image)
		return (1);
	if (mlx_image_to_window(mlx->win, mlx->image, 0, 0) == -1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_mlx		mlx;

	if (1 < argc && ft_strchr(VALID_ARG, argv[1][0]) && argv[1][1] == '\0')
	{
		if (ft_mlx_init(&mlx, argv[1][0]))
			ft_cleanup(1, &mlx);
		mlx_resize_hook(mlx.win, &ft_resize, &mlx);
		mlx_key_hook(mlx.win, &ft_keyhook, &mlx);
		mlx_scroll_hook(mlx.win, &ft_zoom, &mlx);
		mlx_loop_hook(mlx.win, &ft_draw, &mlx);
		mlx_loop(mlx.win);
		ft_cleanup(0, &mlx);
	}
	ft_putstr_fd("Error !\nArgument invalid\n\nm = mandelbrot\n", 2);
	return (1);
}
