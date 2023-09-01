/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   counting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 12:16:57 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/01 15:56:57 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int	st_len_split(char **split)
{
	int	i;
	int	cnt;

	if (split == NULL)
		return (-1);
	if (*split == NULL)
		return (0);
	i = 0;
	cnt = 0;
	while (split[i] != NULL)
	{
		if (split[i][0] > ' ' && split[i][0] <= '~')
			cnt++;
		i++;
	}
	return (cnt);
}

void	fdf_free_split(char **ptr_subs)
{
	int	k;

	if (ptr_subs != NULL)
	{
		k = 0;
		while (ptr_subs[k] != NULL)
		{
			free(ptr_subs[k]);
			k++;
		}
		free(ptr_subs);
	}
}

static int	st_free_upon_error(int fd, char *line, char **split)
{
	if (line != NULL)
		free(line);
	if (split != NULL)
		fdf_free_split(split);
	close(fd);
	return (-1);
}

static int	st_counting_rows_and_columns(int fd, int *rows, int *columns)
{
	char	*line;
	char	**split;

	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), -1);
	(*rows) = 0;
	while (line)
	{
		split = ft_split(line, ' ');
		if (split == NULL)
			return (st_free_upon_error(fd, line, NULL));
		if ((*rows) == 0)
			(*columns) = st_len_split(split);
		else if (st_len_split(split) != (*columns))
			return (st_free_upon_error(fd, line split));
		fdf_free_split(split);
		free(line);
		line = get_next_line(fd);
		(*rows)++;
	}
	return (close(fd), 0);
}

int	fdf_set_rows_and_columns(char **argv, int *rows, int *columns)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || rows == NULL || columns == NULL)
		return (-1);
	return (st_counting_rows_and_columns(fd, rows, columns));
}
