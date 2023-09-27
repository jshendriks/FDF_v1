/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translating.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jagna <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 20:47:49 by jagna         #+#    #+#                 */
/*   Updated: 2023/09/27 11:45:42 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

float	fdf_get_y_translation(t_data *data, t_visual *vis)
{
	float	y_min;
	float	y_max;

	y_max = fdf_max_y_value(data, vis);
	y_min = fdf_min_y_value(data, vis);
	if (fdf_abs_fl(y_min) > fdf_abs_fl((data->image->height) - y_max))
		return ((-1) * y_min);
	else
		return ((data->image->height) - y_max);
}

float	fdf_get_x_translation(t_data *data, t_visual *vis)
{
	float	x_min;
	float	x_max;

	x_max = fdf_max_x_value(data, vis);
	x_min = fdf_min_x_value(data, vis);
	if (fdf_abs_fl(x_min) < fdf_abs_fl((data->image->width) - x_max))
		return ((-1) * x_min);
	else
		return ((data->image->width) - x_max);
}

void	fdf_translate(t_vec *vec1, float translation_x, float translation_y)
{
	float	x_old;
	float	y_old;

	x_old = vec1->x;
	y_old = vec1->y;
	(vec1->x) = x_old + translation_x;
	(vec1->y) = y_old + translation_y;
}
