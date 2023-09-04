/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 10:25:12 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/04 20:17:18 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

void	fdf_isometric_projection(t_vec *vec, int x, int y, int z)
{
	double	angle;

	angle = (M_PI * 45) / 180;
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

/* float	fdf_max_x_value(t_fdf_data *data, float scale, int indicator)
{
	int			x;
	int			y;
	int			**array;
	float		x_max;
	t_fdf_vec	vec;

	y = 0;
	vec.x = 0;
	vec.y = 0;
	array = (data->map->map_coord)[0];
	while (y < (data->map->rows))
	{
		x = 0;
		while (x < (data->map->columns))
		{
			fdf_isometric_projection(&vec, x, y, array[y][x]);
			if (indicator == 0)
				fdf_scale(&vec, scale);
			if (x == 0 && y == 0)
				x_max = vec.x;
			if (vec.x > x_max)
				x_max = vec.x;
			x++;
		}
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
*/
float	fdf_max_y_value(t_data *data, float scale, int indicator)
{
	int	x;
	int	y;
	float	y_max;
	t_vec	vec;

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
				y_max = vec.y;
			if (vec.y > y_max)
				y_max = vec.y;
			x++;
		}
		y++;
	}
	return (y_max);
}

float	fdf_min_y_value(t_data *data, float scale, int indicator)
{
	int	x;
	int	y;
	float	y_min;
	t_vec	vec;

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
				y_min = vec.y;
			if (vec.y < y_min)
				y_min = vec.y;
			x++;
		}
		y++;
	}
	return (y_min);
}
