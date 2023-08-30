/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 10:25:12 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/30 09:54:39 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

void	fdf_isometric_projection(t_fdf_vec *vec, int x, int y, int z)
{
	double	angle;

	angle = (M_PI * 30) / 180;
	if (vec != NULL)
	{
		vec->x = (x - y) * cos(angle);
		vec->y = (x + y) * sin(angle) - z;
	}
}

float	fdf_abs_fl(float nb)
{
	if (nb >= 0)
		return (nb);
	else
		return ((-1) * nb);
}
