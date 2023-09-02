/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_coordinate_array.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 12:53:14 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/02 16:17:41 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

int	fdf_allocate_array(int ***map_coord, t_map_inf *map)
{
	int	row;

	if (map_coord == NULL || map == NULL)
		return (-1);
	if (*map_coord == NULL)
		return (-1);
	row = 0;
	while (row < (map->rows))
	{
		(*map_coord)[row] = malloc((map->columns) * sizeof(int));
		if ((*map_coord)[row] == NULL)
		{
			fdf_free_int_array_until_j(map_coord, row, map);
			return (-1);
		}
		row++;
	}
	return (row);
}

static int	st_init_row(char **split, int ***coord, int row, t_map_inf *map)
{
	int	column;
	int	flow;
	int	z;

	if (split == NULL || coord == NULL || map == NULL)
		return (-1);
	if (*coord == NULL)
		return (-1);
	column = 0;
	while (split[column] && column < (map->columns))
	{
		z = 0;
		if (split[column][0] > ' ' && split[column][0] <= '~')
		{
			flow = fdf_atoi_overflw((const char *)split[column], &z);
			if (flow == 0)
				return (-1);
			(*coord)[row][column] = z;
		}
		column++;
	}
	return (column);
}

static void	st_free_error(int fd, char *line, char **split)
{
	if (line != NULL)
		free(line);
	if (split != NULL)
		fdf_free_split(split);
	close(fd);
}

static int	st_init_array(int ***map_coord, t_map_inf *map, int fd)
{
	int		row;
	char	*line;
	char	**split;

	line = get_next_line(fd);
	if (line == NULL)
		return (st_free_error(fd, line, NULL), -1);
	row = 0;
	while (line && row < (map->rows))
	{
		split = ft_split(line, ' ');
		if (split == NULL)
		{
			fdf_free_int_array_until_j(map_coord, (map->rows), map);
			return (st_free_error(fd, line, split), -1);
		}
		st_init_row(split, map_coord, row, map);
		free(line);
		fdf_free_split(split);
		line = get_next_line(fd);
		row++;
	}
	return (st_free_error(fd, line, split), (map->size));
}

int	fdf_init_coord_array(char **argv, int ***map_coord, t_map_inf *map)
{
	int		fd;

	if (argv == NULL || map_coord == NULL)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	return (st_init_array(map_coord, map, fd));
}
