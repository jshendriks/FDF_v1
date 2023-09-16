/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scaling_translating.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 16:59:17 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/04 20:55:15 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static float	st_get_yaxis_scale(t_data *data)
{
	float	y_max;
	float	y_min;

	y_max = fdf_max_y_value(data, 0, 1);
	y_min = fdf_min_y_value(data, 0, 1);

	if (fdf_abs_fl(y_max - y_min) + 2 == 0)
		return (1);
	return ((data->image->height) / (fdf_abs_fl(y_max - y_min) + 2));
}

static float	st_get_xaxis_scale(t_data *data)
{
	float	x_max;
	float	x_min;

	x_max = fdf_max_x_value(data, 0, 1);
	x_min = fdf_min_x_value(data, 0, 1);

	if (fdf_abs_fl(x_max - x_min) + 2 == 0)
		return (1);
	return ((data->image->width) / (fdf_abs_fl(x_max - x_min) + 2));
}

float	fdf_get_scale(t_data *data)
{
	float	x_scale;
	float	y_scale;

	x_scale = st_get_xaxis_scale(data);
	y_scale = st_get_yaxis_scale(data);
	if (x_scale < y_scale)
		return (x_scale);
	else
		return (y_scale);
} 

/* float	fdf_get_translation(t_fdf_data *data, float scale)
{
	float	x_min;
	float	x_max;
	float	y_min;
	float	y_max;

	x_min = fdf_min_x_value(data, scale, 0);
	y_min = fdf_min_y_value(data, scale, 0);
	x_max = fdf_max_x_value(data, scale, 0);
	y_max = fdf_max_y_value(data, scale, 0);

	if (x_min < 0 || y_min < 0)
	{
		if (fdf_abs_fl(x_min) > fdf_abs_fl(y_min))
			return (fdf_abs_fl(x_min));
		else
			return (fdf_abs_fl(y_min));
	}
	else
	{
		if (y_max > (data->image->height))
			return ((data->image->height) - y_max);
		else if (x_max > (data->image->width))
			return ((data->image->width) - x_max);
		else
			return (0);
	}
		
} */

float	fdf_get_y_translation(t_data *data, float scale)
{
	float	y_min;
	float	y_max;

	y_max = fdf_max_y_value(data, scale, 0);
	y_min = fdf_min_y_value(data, scale, 0);

	if (fdf_abs_fl(y_min) < fdf_abs_fl((data->image->height) - y_max))
		return ((-1) * y_min);
	else
		return ((data->image->height) - y_max);
}

float	fdf_get_x_translation(t_data *data, float scale)
{
	float	x_min;
	float	x_max;

	x_max = fdf_max_x_value(data, scale, 0);
	x_min = fdf_min_x_value(data, scale, 0);

	if (fdf_abs_fl(x_min) < fdf_abs_fl((data->image->width) - x_max))
		return ((-1) * x_min);
	else
		return ((data->image->width) - x_max);
}

/* float	fdf_get_translation(t_fdf_data *data, float scale)
{
	float	x_translation;
	float	y_translation;

	x_translation = st_get_x_translation(data, scale);
	y_translation = st_get_y_translation(data, scale);

	if (fdf_abs_fl(x_translation) > fdf_abs_fl(y_translation))
		return (x_translation);
	else
		return (y_translation);
} */

void	fdf_scale(t_vec *vec1, float scale)
{
	float	x_old;
	float	y_old;

	x_old = vec1->x;
	y_old = vec1->y;
	(vec1->x) = scale * x_old;
	(vec1->y) = scale * y_old;
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
