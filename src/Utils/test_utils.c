/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 13:44:46 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/28 14:57:05 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

void	fdf_print_array(t_fdf_map_info *map)
{
	int	i;
	int	j;
	int	**array;

	if (map != NULL)
	{
		array = *(map->map_coord);
		if (array == NULL)
			ft_printf("(NULL)\n");
		else
		{
			i = 0;
			while (i < (map->rows))
			{
				ft_printf("Row %i: \n", i);
				j = 0;
				while (j < (map->columns))
				{
					ft_printf("\t Column %i: \t z: %i\n", j, array[i][j]);
					j++;
				}
				i++;
			}
		}
	}
}

void	fdf_print_image_info(t_fdf_image_info *image)
{
	ft_printf("IMAGE INFO\n");
	if (image != NULL)
	{
		ft_printf(" \t width: %i \n \t height: %i \n", image->width, image->height);
		ft_printf(" \t mlx_img pointer: %p \n \t mlx pointer: %p\n", image->img, image->mlx);
	}
	else 
		ft_printf("(NULL)\n");
	ft_printf("..........\n");
}

void	fdf_print_map_info(t_fdf_map_info *map)
{
	ft_printf("MAP INFO\n");
	if (map != NULL)
	{
		ft_printf("Can I access map info??\n");
		ft_printf(" \t size: %i \n \t columns: %i \n \t rows: %i\n", map->size, map->columns, map->rows);
		ft_printf(" \t array of coordinates: \n");
		fdf_print_array(map);
	}
	else {
		ft_printf("(NULL)\n");
	}
	ft_printf("..........\n");
}

void	fdf_print_data(t_fdf_data *data)
{
	ft_printf("Printing data\n");
	if (data == NULL)
		ft_printf("(NULL)\n");
	else
	{	
		fdf_print_image_info(data->image);
		fdf_print_map_info(data->map);
	}
	ft_printf(".............................\n");
}
