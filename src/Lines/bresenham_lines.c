/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bresenham_lines.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 10:57:13 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/04 20:24:42 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int	st_give_sign(float a)
{
	if (a < 0)
		return (-1);
	else
		return (1);
}

static void	st_draw_line_incrementing_x(t_vec vec_from, t_vec vec_to, t_bresenham line, t_data *data)
{
	float	x;
	float	y;

	if (line.sign_dx < 0)
		fdf_bresenham_line(vec_to, vec_from, data);
	else
	{
		x = vec_from.x;
		y = vec_from.y;
		while (x <= (vec_to.x))
		{
			if (x > 0 && x < (data->image->width))
			{
				if (y > 0 && y < (data->image->height))
					mlx_put_pixel((data->image->img), (int)x, (int)y, 0xFFFFFFFF);
			}
			(line.eps) += (line.dy);
			if ((2 * (line.eps)) >= (line.dx))
			{
				y += (line.sign_dy);
				(line.eps) -= (line.dx);
			}
			x += (line.sign_dx);
		}
	}
}

static void	st_draw_line_incrementing_y(t_vec vec_from, t_vec vec_to, t_bresenham line, t_data *data)
{
	float	x;
	float	y;

	if (line.sign_dy < 0)
		fdf_bresenham_line(vec_to, vec_from, data);
	else
	{
		x = vec_from.x;
		y = vec_from.y;
		while (y <= (vec_to.y))
		{
			if (x > 0 && x < (data->image->width))
			{
				if (y > 0 && y < (data->image->height))
					mlx_put_pixel((data->image->img), (int)x, (int)y, 0xFFFFFFFF);
			}
			(line.eps) += (line.dx);
			if ((2 * (line.eps)) >= (line.dy))
			{
				x += (line.sign_dx);
				(line.eps) -= (line.dy);
			}
			y += (line.sign_dy);
		}
	}
}

void	fdf_bresenham_line(t_vec vec_from, t_vec vec_to, t_data *data)
{
	t_bresenham	line;

	line.dx = fdf_abs_fl((vec_to.x) - (vec_from.x));
	line.sign_dx = st_give_sign((vec_to.x) - (vec_from.x));
	line.dy = fdf_abs_fl((vec_to.y) - (vec_from.y));
	line.sign_dy = st_give_sign((vec_to.y) - (vec_from.y));
	line.eps = 0;
	if (line.dx > line.dy)
		st_draw_line_incrementing_x(vec_from, vec_to, line, data);
	else
		st_draw_line_incrementing_y(vec_from, vec_to, line, data);
}
