/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_scale_mult.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jagna <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 12:24:52 by jagna         #+#    #+#                 */
/*   Updated: 2023/09/27 12:25:42 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static float	st_get_yaxis_scale_mult(t_data *data)
{
	float	y_max;
	float	y_min;

	y_max = fdf_max_y_value(data, NULL);
	y_min = fdf_min_y_value(data, NULL);
	if (fdf_abs_fl(y_max - y_min) == 0)
		return (1);
	return ((data->image->height) / (fdf_abs_fl(y_max - y_min)));
}

static float	st_get_xaxis_scale_mult(t_data *data)
{
	float	x_max;
	float	x_min;

	x_max = fdf_max_x_value(data, NULL);
	x_min = fdf_min_x_value(data, NULL);
	if (fdf_abs_fl(x_max - x_min) == 0)
		return (1);
	return ((data->image->width) / (fdf_abs_fl(x_max - x_min)));
}

float	fdf_get_scale_mult(t_data *data)
{
	float	x_scale;
	float	y_scale;

	x_scale = st_get_xaxis_scale_mult(data);
	y_scale = st_get_yaxis_scale_mult(data);
	if (x_scale < y_scale)
		return (x_scale * 0.9);
	else
		return (y_scale * 0.9);
}
