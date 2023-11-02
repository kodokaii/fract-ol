/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:22:49 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/02 20:55:46 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_mlx_init(t_mlx *mlx)
{
	mlx->win = NULL;
	mlx->image = NULL;
	mlx->fract.center[0] = 0.0L;
	mlx->fract.center[1] = 0.0L;
	mlx->fract.radius = 2.0L;
	mlx->fract.iter = 21.0L;
	if (!mlx->fract.pow)
		mlx->fract.pow = 3.0L;
	mlx->fract.color = COLOR_COUNT;
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

static int	ft_get_fractal(t_mlx *mlx, int argc, char **argv)
{
	mlx->fract.type = FRACT_COUNT;
	if (1 < argc)
	{
		if (!ft_strncmp(argv[1], "m", 2))
			mlx->fract.type = 0;
		else if (!ft_strncmp(argv[1], "j", 2))
			mlx->fract.type = 1;
		else if (!ft_strncmp(argv[1], "b", 2))
			mlx->fract.type = 2;
		else if (!ft_strncmp(argv[1], "mm", 3))
			mlx->fract.type = 3;
		if (2 < argc)
			mlx->fract.z0[0] = ft_atof(argv[2]);
		if (3 < argc)
			mlx->fract.z0[1] = ft_atof(argv[3]);
		if (4 < argc)
			mlx->fract.pow = ft_atof(argv[4]);
		if (mlx->fract.type != FRACT_COUNT)
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	static t_mlx		mlx = {};

	if (ft_get_fractal(&mlx, argc, argv))
	{
		if (ft_mlx_init(&mlx))
			ft_cleanup(1, &mlx);
		mlx_resize_hook(mlx.win, &ft_resize_hook, &mlx);
		mlx_key_hook(mlx.win, &ft_key_hook, &mlx);
		mlx_scroll_hook(mlx.win, &ft_scroll_hook, &mlx);
		mlx_loop_hook(mlx.win, &ft_draw, &mlx);
		mlx_loop(mlx.win);
		ft_cleanup(0, &mlx);
	}
	ft_putstr_fd(MESSAGE_ERROR, 2);
	return (1);
}
