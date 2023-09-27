/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scaling.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jagna <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 20:43:54 by jagna         #+#    #+#                 */
/*   Updated: 2023/09/27 11:46:22 by jagna         ########   odam.nl         */
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

static float	st_get_yaxis_scale_div(t_data *data)
{
	float	y_max;
	float	y_min;

	y_max = fdf_max_y_value(data, NULL);
	y_min = fdf_min_y_value(data, NULL);
	if (fdf_abs_fl(y_max - y_min) == 0)
		return (1);
	return ((fdf_abs_fl(y_max - y_min)) / (data->image->height));
}

static float	st_get_xaxis_scale_div(t_data *data)
{
	float	x_max;
	float	x_min;

	x_max = fdf_max_x_value(data, NULL);
	x_min = fdf_min_x_value(data, NULL);
	if (fdf_abs_fl(x_max - x_min) == 0)
		return (1);
	return ((fdf_abs_fl(x_max - x_min)) / (data->image->width));
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

float	fdf_get_scale_div(t_data *data)
{
	float	x_scale;
	float	y_scale;

	x_scale = st_get_xaxis_scale_div(data);
	y_scale = st_get_yaxis_scale_div(data);
	if (x_scale > y_scale)
		return (x_scale * 1.1);
	else
		return (y_scale * 1.1);
}

void	fdf_scale(t_vec *vec1, t_visual *vis)
{
	float	x_old;
	float	y_old;

	if (vec1 != NULL && vis != NULL)
	{
		x_old = vec1->x;
		y_old = vec1->y;
		if (vis->scale_mult < 1)
		{
			(vec1->x) = x_old / (vis->scale_div);
			(vec1->y) = y_old / (vis->scale_div);
		}
		else
		{
			(vec1->x) = (vis->scale_mult) * x_old;
			(vec1->y) = (vis->scale_mult) * y_old;
		}
	}
}
