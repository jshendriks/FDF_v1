/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:45:33 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/28 11:46:46 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

int	fdf_arg_check(int argc, char **argv)
{
	int	fd;

	if (argc != 2 || argv == NULL)
		return (-1);
	if (*argv == NULL)
		return (-1);
	if (ft_strlen(argv[1]) < 4)
		return (-1);
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == NULL)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}
