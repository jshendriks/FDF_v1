/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scaling.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jagna <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 20:43:54 by jagna         #+#    #+#                 */
/*   Updated: 2023/09/16 18:02:29 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static float	st_get_yaxis_scale(t_data *data)
{
	float	y_max;
	float	y_min;

	y_max = fdf_max_y_value(data, 0, 1);
	y_min = fdf_min_y_value(data, 0, 1);
	if (fdf_abs_fl(y_max - y_min) == 0)
		return (1);
	return ((data->image->height) / (fdf_abs_fl(y_max - y_min)));
}

static float	st_get_xaxis_scale(t_data *data)
{
	float	x_max;
	float	x_min;

	x_max = fdf_max_x_value(data, 0, 1);
	x_min = fdf_min_x_value(data, 0, 1);
	if (fdf_abs_fl(x_max - x_min) == 0)
		return (1);
	return ((data->image->width) / (fdf_abs_fl(x_max - x_min)));
}

float	fdf_get_scale(t_data *data)
{
	float	x_scale;
	float	y_scale;

	x_scale = st_get_xaxis_scale(data);
	y_scale = st_get_yaxis_scale(data);
	if (x_scale < y_scale)
		return (x_scale / 2);
	else
		return (y_scale / 2);
}

void	fdf_scale(t_vec *vec1, float scale)
{
	float	x_old;
	float	y_old;

	x_old = vec1->x;
	y_old = vec1->y;
	(vec1->x) = scale * x_old;
	(vec1->y) = scale * y_old;
}
