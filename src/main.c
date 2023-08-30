/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:39:39 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/30 10:14:33 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

/* TO DODO:
			- Escape key to close window 
			- Find apropriate scale
			- Find apropriate translation
			- Fix what is causing some files.fdf to look weird
				Weird looking files:
									+ 10-2
									+ 10-70
									+ 42
									+ 20-60
									+ pentenegpos
									+ pyra
									+ t1
			- Fix that lines which you should not see do not get drawn
				Example:
						+ pylone
						+ 42
						+ t1
*/

static int32_t	st_error_nofreeing(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

static void	st_terminate_map_info(t_fdf_map_info *map)
{
	fdf_free_int_array_until_j(map->map_coord, map->rows,map);
	free(map->map_coord);
	free(map);
}

static void	st_terminate_image_info(t_fdf_image_info *image)
{
	mlx_delete_image(image->mlx, image->img);
	mlx_terminate(image->mlx);
	free(image);
}

static void	st_terminate_data_struct(t_fdf_data **data)
{
	st_terminate_image_info((*data)->image);
	st_terminate_map_info((*data)->map);
	free(*data);
	data = NULL;
}

int32_t	main(int argc, char **argv)
{
	t_fdf_data	*data;

	if (fdf_arg_check(argc, argv) == -1)
		st_error_nofreeing("Wrong input, usage: ./fdf [NAME OF FILE].fdf \n");
	data = malloc(sizeof(t_fdf_data));
	if (data == NULL)
		st_error_nofreeing("Failed to create data struct \n");
	fdf_init_data(data, argv);
	fdf_print_data(data);
	fdf_draw_lines(data);
	if (mlx_image_to_window(data->image->mlx, data->image->img, 0, 0) < 0)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		st_terminate_data_struct(&data);
		exit(EXIT_FAILURE);
	}
	mlx_loop(data->image->mlx);
	st_terminate_data_struct(&data);
	exit(EXIT_SUCCESS);
}
