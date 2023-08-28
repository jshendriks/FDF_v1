/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:39:39 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/28 14:33:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int	st_error_nofreeing(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
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
	exit(EXIT_SUCCESS);
}
