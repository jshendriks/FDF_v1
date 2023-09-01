/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminate.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 15:22:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/01 15:23:34 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

void	fdf_terminate_map_info(t_fdf_map_info *map)
{
	fdf_free_int_array_until_j(map->map_coord, map->rows, map);
	free(map->map_coord);
	free(map);
}

void	fdf_terminate_image_info(t_fdf_image_info *image)
{
	mlx_delete_image(image->mlx, image->img);
	mlx_terminate(image->mlx);
	free(image);
}

void	fdf_terminate_data_struct(t_fdf_data **data)
{
	fdf_terminate_image_info((*data)->image);
	fdf_terminate_map_info((*data)->map);
	free(*data);
	data = NULL;
}
