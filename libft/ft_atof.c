/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/10/31 20:54:37 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_decimal_part(const char **str)
{
	double	res;

	res = 0;
	while (ft_isdigit(**str))
	{
		res *= 10;
		res += **str - '0';
		(*str)++;
	}
	return (res);
}

static double	ft_fractional_part(const char *str)
{
	double	res;

	res = 0;
	while (ft_isdigit(*str))
	{
		res += *str - '0';
		res /= 10;
		str++;
	}
	return (res);
}

double	ft_atof(const char *str)
{
	double	res;
	double	sign;

	res = 0;
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = ft_decimal_part(&str);
	if (*str == '.')
		res += ft_fractional_part(++str);
	return (res * sign);
}
