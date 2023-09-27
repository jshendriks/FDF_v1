/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   critical_values_y.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jagna <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 20:36:40 by jagna         #+#    #+#                 */
/*   Updated: 2023/09/27 11:52:08 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static void	st_check_row_ymax(t_data *data, float *y_max, t_crit buc)
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
		if (buc.visual != NULL)
			fdf_scale(&vec, buc.visual);
		if (x == 0 && buc.y == 0)
			(*y_max) = vec.y;
		if (vec.y > (*y_max))
			(*y_max) = vec.y;
		x++;
	}
}

float	fdf_max_y_value(t_data *data, t_visual *visual)
{
	int		y;
	float	y_max;
	t_crit	buc;

	y = 0;
	y_max = 0;
	buc.y = y;
	buc.visual = visual;
	while (y < (data->map->rows))
	{
		buc.y = y;
		st_check_row_ymax(data, &y_max, buc);
		y++;
	}
	return (y_max);
}

static void	st_check_row_ymin(t_data *data, float *y_min, t_crit buc)
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
		if (buc.visual != NULL)
			fdf_scale(&vec, buc.visual);
		if (x == 0 && buc.y == 0)
			(*y_min) = vec.y;
		if (vec.y < (*y_min))
			(*y_min) = vec.y;
		x++;
	}
}

float	fdf_min_y_value(t_data *data, t_visual *visual)
{
	int		y;
	float	y_min;
	t_crit	buc;

	y = 0;
	y_min = 0;
	buc.y = y;
	buc.visual = visual;
	while (y < (data->map->rows))
	{
		st_check_row_ymin(data, &y_min, buc);
		y++;
	}
	return (y_min);
}
