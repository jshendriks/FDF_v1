/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:39:39 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/04 20:31:02 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int32_t	st_error_nofreeing(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

void	fdf_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf("Exiting ...\n");
		fdf_terminate_data_struct((t_data **)&param);
		exit(EXIT_SUCCESS);
	}
}

int32_t	main(int argc, char **argv)
{
	t_data	*data;

	if (fdf_arg_check(argc, argv) == -1)
		st_error_nofreeing("Wrong input, usage: ./fdf [NAME OF FILE].fdf \n");
	data = malloc(sizeof(t_data));
	if (data == NULL)
		st_error_nofreeing("Failed to create data struct \n");
	fdf_init_data(data, argv);
	fdf_print_data(data);
	fdf_draw_lines(data);
	if (mlx_image_to_window(data->image->mlx, data->image->img, 0, 0) < 0)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		fdf_terminate_data_struct(&data);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(data->image->mlx, &fdf_keyhook, data);
	mlx_loop(data->image->mlx);
	fdf_terminate_data_struct(&data);
	exit(EXIT_SUCCESS);
}
