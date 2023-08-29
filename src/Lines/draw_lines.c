/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_lines.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 10:06:32 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/29 10:45:06 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static void	st_decide_line(t_fdf_vec vec_from, t_fdf_vec vec_to, t_fdf_data *data)
{
	if (vec_from.x == vec_to.x)
		fdf_vertical_line(vec_from, vec_to, data);
	else if (vec_from.y == vec_to.y)
		fdf_horizontal_line(vec_from, vec_to, data);
	else
		fdf_bresenham_line(vec_from, vec_to, data);
}

static void	st_draw_line_neighbour_toright(t_fdf_data *data, int y, int x)
{
	int	**array;
	t_fdf_vec	vec_from;
	t_fdf_vec	vec_to;

	if (data != NULL)
	{
		if ((x + 1) < (data->map->columns))
		{
			vec_from.x = 0;
			vec_from.y = 0;
			vec_to.x = 0;
			vec_to.y = 0;
			array = *((data->map)->map_coord);
			fdf_isometric_projection(&vec_from, x, y, array[y][x]);
			fdf_isometric_projection(&vec_to, x + 1, y, array[y][x + 1]);
			st_decide_line(vec_from, vec_to, data);
		}
	}
}

static void	st_draw_line_neighbour_under(t_fdf_data *data, int y, int x)
{
	int	**array;
	t_fdf_vec	vec_from;
	t_fdf_vec	vec_to;

	if (data != NULL)
	{
		if ((y + 1) < (data->map->rows))
		{
			vec_from.x = 0;
			vec_from.y = 0;
			vec_to.x = 0;
			vec_to.y = 0;
			array = *((data->map)->map_coord);
			fdf_isometric_projection(&vec_from, x, y, array[y][x]);
			fdf_isometric_projection(&vec_to, x, y + 1, array[y + 1][x]);
			st_decide_line(vec_from, vec_to, data);
		}
	}
}

void	fdf_draw_lines(t_fdf_data *data)
{
	int	x;
	int	y;

	if (data != NULL)
	{
		y = 0;
		while (y < (data->map->rows))
		{
			x = 0;
			while (x < (data->map->columns))
			{
				st_draw_line_neighbour_toright(data, y, x);
				st_draw_line_neighbour_under(data, y, x);
				x++;
			}
			y++;
		}
	}
}
