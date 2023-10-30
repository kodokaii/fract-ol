/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/30 21:01:17 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define FT_WIDTH		1080
# define FT_HEIGHT		1080

# define FRACT_COUNT	1
# define VALID_ARG		"m"

typedef struct s_fractol
{
	double	center[2];
	double	z0[2];
	double	radius;
	double	ratio;
	double	iter;
	t_uint	type;
	t_uint	color;
}	t_fractol;

typedef struct s_mlx
{
	mlx_t		*win;
	mlx_image_t	*image;
	t_fractol	fract;
}	t_mlx;

void	ft_resize(int width, int heigth, void *param);
void	ft_zoom(double xdelta, double ydelta, void *param);
void	ft_keyhook(mlx_key_data_t keydata, void *param);
int		ft_color(t_mlx *mlx, double i, double distance);
void	ft_draw(void *param);

int		ft_mandelbrot(float x, float y, t_mlx *mlx);

void	ft_cleanup(int returnCode, t_mlx *mlx);
int		ft_pixel(float r, float g, float b, float a);
void	ft_pixel_iter(mlx_image_t *image, t_mlx *mlx,
			int (*f)(float, float, t_mlx *));

#endif
