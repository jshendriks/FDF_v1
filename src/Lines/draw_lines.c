/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_lines.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 10:06:32 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/16 18:05:28 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static void	st_decide_line(t_vec vec_from, t_vec vec_to, t_data *data)
{
	if (vec_from.x == vec_to.x)
		fdf_vertical_line(vec_from, vec_to, data);
	else if (vec_from.y == vec_to.y)
		fdf_horizontal_line(vec_from, vec_to, data);
	else
		fdf_bresenham_line(vec_from, vec_to, data);
}

static void	st_nghbr_toright(t_data *data, int y, int x, t_visual visual)
{
	int		**array;
	t_vec	vec_from;
	t_vec	vec_to;

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
			fdf_scale(&vec_from, visual.scale);
			fdf_translate(&vec_from, visual.transl_x, visual.transl_y);
			fdf_scale(&vec_to, visual.scale);
			fdf_translate(&vec_to, visual.transl_x, visual.transl_y);
			st_decide_line(vec_from, vec_to, data);
		}
	}
}

static void	st_nghbr_under(t_data *data, int y, int x, t_visual visual)
{
	int		**array;
	t_vec	vec_from;
	t_vec	vec_to;

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
			fdf_scale(&vec_from, visual.scale);
			fdf_translate(&vec_from, visual.transl_x, visual.transl_y);
			fdf_scale(&vec_to, visual.scale);
			fdf_translate(&vec_to, visual.transl_x, visual.transl_y);
			st_decide_line(vec_from, vec_to, data);
		}
	}
}

void	fdf_draw_lines(t_data *data)
{
	int			x;
	int			y;
	t_visual	visual;

	if (data != NULL)
	{
		visual.scale = fdf_get_scale(data);
	//	visual.scale = 60;
		visual.transl_x = fdf_get_x_translation(data, visual.scale);
		visual.transl_y = fdf_get_y_translation(data, visual.scale);
//		visual.transl_y = 500;
		fdf_print_visual_info(&visual);
		y = 0;
		while (y < (data->map->rows))
		{
			x = 0;
			while (x < (data->map->columns))
			{
				st_nghbr_toright(data, y, x, visual);
				st_nghbr_under(data, y, x, visual);
				x++;
			}
			y++;
		}
	}
}
