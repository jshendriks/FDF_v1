/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:45:33 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/16 15:58:44 by jagna         ########   odam.nl         */
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

void	fdf_free_int_array_until_j(int ***map_coord, int j, t_map_inf *map)
{
	int	i;

	if (j > (map->rows))
		j = (map->rows);
	if (map_coord != NULL)
	{
		i = 0;
		while (i < j)
		{
			free((*map_coord)[i]);
			i++;
		}
		free(*map_coord);
		*map_coord = NULL;
	}
}
