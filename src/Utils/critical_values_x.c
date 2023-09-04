/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   critical_values_x.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 16:02:40 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/04 20:16:32 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static void	st_check_row_xmax(t_data *data, float *x_max, t_crit buc)
{
	int		x;
	int		**array;
	t_vec	vec;

	x = 0;
	vec.x = 0;
	vec.y = 0;
	array = (data->map->map_coord)[0];
	while (x < (data->map->columns))
	{
		fdf_isometric_projection(&vec, x, buc.y, array[buc.y][x]);
		if (buc.indicator == 0)
			fdf_scale(&vec, buc.scale);
		if (x == 0 && buc.y == 0)
			(*x_max) = vec.x;
		if (vec.x > (*x_max))
			(*x_max) = vec.x;
		x++;
	}
}

float	fdf_max_x_value(t_data *data, float scale, int indicator)
{
	int		y;
	float	x_max;
	t_crit	buc;

	y = 0;
	x_max = 0;
	buc.y = y;
	buc.indicator = indicator;
	buc.scale = scale;
	while (y < (data->map->rows))
	{
		buc.y = y;
		st_check_row_xmax(data, &x_max, buc);
		y++;
	}
	return (x_max);
}

static void	st_check_row_xmin(t_data *data, float *x_min, t_crit buc)
{
	int			x;
	int			**array;
	t_vec	vec;

	x = 0;
	vec.x = 0;
	vec.y = 0;
	array = (data->map->map_coord)[0];
	while (x < (data->map->columns))
	{
		fdf_isometric_projection(&vec, x, buc.y, array[buc.y][x]);
		if (buc.indicator == 0)
			fdf_scale(&vec, buc.scale);
		if (x == 0 && buc.y == 0)
			(*x_min) = vec.x;
		if (vec.x < (*x_min))
			(*x_min) = vec.x;
		x++;
	}
}

float	fdf_min_x_value(t_data *data, float scale, int indicator)
{
	int			y;
	float		x_min;
	t_crit	buc;

	y = 0;
	x_min = 0;
	buc.y = y;
	buc.indicator = indicator;
	buc.scale = scale;
	while (y < (data->map->rows))
	{
		buc.y = y;
		st_check_row_xmin(data, &x_min, buc);
		y++;
	}
	return (x_min);
}
