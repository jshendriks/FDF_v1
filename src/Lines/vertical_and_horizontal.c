/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vertical_and_horizontal.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 10:48:00 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/30 09:56:16 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"
static int	st_return_upperbound_and_set_beginning(int a, int b, int *nb)
{
	if (a < b)
	{
		(*nb) = a;
		return (b);
	}
	else
	{
		(*nb) = b;
		return (a);
	}
}

void	fdf_vertical_line(t_fdf_vec vec_from, t_fdf_vec vec_to, t_fdf_data *data)
{
	int	x;
	int	y;
	int	upper_bound;

	if (data != NULL)
	{
		if (vec_from.x == vec_to.x)
		{
			x = vec_from.x;
			y = 0;
			upper_bound = st_return_upperbound_and_set_beginning(vec_from.y, vec_to.y, &y);
			while (y <= upper_bound)
			{
				if (x > 0 && x < (data->image->width))
				{
					if (y > 0 && y < (data->image->height))
						mlx_put_pixel((data->image->img), (int)x, (int)y, 0xFFFFFFFF);
				}
				y++;
			}
		}
	}
}

void	fdf_horizontal_line(t_fdf_vec vec_from, t_fdf_vec vec_to, t_fdf_data *data)
{
	int	x;
	int	y;
	int	upper_bound;

	if (data != NULL)
	{
		if (vec_from.y == vec_to.y)
		{
			y = vec_from.y;
			x = 0;
			upper_bound = st_return_upperbound_and_set_beginning(vec_from.x, vec_to.x, &x);
			while (x <= upper_bound)
			{
				if (x > 0 && x < (data->image->width))
				{
					if (y > 0 && y < (data->image->height))
						mlx_put_pixel((data->image->img), (int)x, (int)y, 0xFFFFFFFF);
				}
				x++;
			}
		}
	}
}
