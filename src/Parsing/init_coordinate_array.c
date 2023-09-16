/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_coordinate_array.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 12:53:14 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/16 15:51:28 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

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

int fdf_allocate_array(int ***map_coord, t_map_inf *map)
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

static int	st_init_row(char **split, int ***map_coord, int row, t_map_inf *map)
{
	int	column;
	int	flow;
	int	z;

	if (split == NULL || map_coord == NULL || map == NULL)
		return (-1);
	if (*map_coord == NULL)
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
			(*map_coord)[row][column] = z;
		}
		column++;
	}
	return (column);
}

/* int	fdf_init_coordinate_array(char **argv, int ***map_coord, t_map_inf *map)
{
	int		row;
	int		column;
	int		fd;
	char	*line;
	char	**split;

	if (argv == NULL || map_coord == NULL)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (fdf_free_int_array_until_j(map_coord, (map->rows), map), -1);
	}
	row = 0;
	while (line && row < (map->rows))
	{
		split = ft_split(line, ' ');
		if (split == NULL)
		{
			close(fd);
			free(line);
			fdf_free_int_array_until_j(map_coord, (map->rows), map);
			return (-1);
		}
		column = st_init_coordinate_row(split, map_coord, row, map);
		if (column != (map->columns))
		{
			close(fd);
			free(line);
			fdf_free_int_array_until_j(map_coord, (map->rows), map);
			fdf_free_split(split);
			return (-1);
		}
		free(line);
		fdf_free_split(split);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	if (line != NULL)
		free(line);
	return ((map->size));
} */
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
	return (close(fd), (map->size));
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
