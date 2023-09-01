/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   critical_values_x.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 16:02:40 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/01 16:11:22 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static void	st_check_row_max_x_value(t_fdf_data *data, int y, float *max_x, int **array, int indicator)
{
	int			x;
	t_fdf_vec	vec;

	x = 0;
	vec.x = 0;
	vec.y = 0;
	while (x < (data->map->columns))
	{
		fdf_isometric_projection(&vec, x, y, array[y][x]);
		if (indicator == 0)
			fdf_scale(&vec, scale);
		if (x == 0 && y == 0)
			(*x_max) = vec.x;
		if (vec.x > x_max)
			(*x_max) = vec.x;
		x++;
	}
}

float	fdf_max_x_value(t_fdf_data *data, float scale, int indicator)
{
	int			x;
	int			y;
	int			**array;
	float		x_max;

	y = 0;
	array = (data->map->map_coord)[0];
	x_max = 0;
	while (y < (data->map->rows))
	{
		st_check_row_max_x_value(data, y, &max_x, array, indicator);
		y++;
	}
	return (x_max);
}

float	fdf_min_x_value(t_fdf_data *data, float scale, int indicator)
{
	int	x;
	int	y;
	float	x_min;
	t_fdf_vec	vec;

	y = 0;
	vec.x = 0;
	vec.y = 0;
	while (y < (data->map->rows))
	{
		x = 0;
		while (x < (data->map->columns))
		{
			fdf_isometric_projection(&vec, x, y, (data->map->map_coord)[0][y][x]);
			if (indicator == 0)
				fdf_scale(&vec, scale);
			if (x == 0 && y == 0)
				x_min = vec.x;
			if (vec.x < x_min)
				x_min = vec.x;
			x++;
		}
		y++;
	}
	return (x_min);
}
