/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bresenham_lines.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 10:57:13 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/16 17:17:38 by jagna         ########   odam.nl         */
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

static void	stdraw_incrx(t_vec from, t_vec to, t_bresenham line, t_data *data)
{
	int	x;
	int	y;

	if (line.sign_dx < 0)
		fdf_bresenham_line(to, from, data);
	else
	{
		x = from.x;
		y = from.y;
		while (x <= (int)(to.x))
		{
			if (x > 0 && x < (data->image->width))
			{
				if (y > 0 && y < (data->image->height))
					mlx_put_pixel(data->image->img, x, y, 0xFFFFFFFF);
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

static void	stdraw_incry(t_vec from, t_vec to, t_bresenham line, t_data *data)
{
	int	x;
	int	y;

	if (line.sign_dy < 0)
		fdf_bresenham_line(to, from, data);
	else
	{
		x = from.x;
		y = from.y;
		while (y <= (int)(to.y))
		{
			if (x > 0 && x < (data->image->width))
			{
				if (y > 0 && y < (data->image->height))
					mlx_put_pixel((data->image->img), x, y, 0xFFFFFFFF);
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
		stdraw_incrx(vec_from, vec_to, line, data);
	else
		stdraw_incry(vec_from, vec_to, line, data);
}
