/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scaling_translating.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 16:59:17 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/29 17:06:53 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

void	fdf_scale(t_fdf_vec *vec1, t_fdf_vec *vec2, float scale)
{
	float	x_old;
	float	y_old;

	x_old = vec1->x;
	y_old = vec1->y;
	(vec1->x) = scale * x_old;
	(vec1->y) = scale * y_old;
	x_old = vec2->x;
	y_old = vec2->y;
	(vec2->x) = scale * x_old;
	(vec2->y) = scale * y_old;
}

void	fdf_translate(t_fdf_vec *vec1, t_fdf_vec *vec2, float translation)
{
	float	x_old;
	float	y_old;

	x_old = vec1->x;
	y_old = vec1->y;
	(vec1->x) = x_old + translation;
	(vec1->y) = y_old + translation;
	x_old = vec2->x;
	y_old = vec2->y;
	(vec2->x) = x_old + translation;
	(vec2->y) = y_old + translation;
}
