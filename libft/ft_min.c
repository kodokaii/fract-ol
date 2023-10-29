/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/29 16:21:52 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_min_int(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

t_uint	ft_min_uint(t_uint a, t_uint b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	ft_min_size_t(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

ssize_t	ft_min_ssize(ssize_t a, ssize_t b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_min_float(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}