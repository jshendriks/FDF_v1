/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   counting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 12:16:57 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/28 14:41:43 by jhendrik      ########   odam.nl         */
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

int	fdf_counting_rows_and_columns(char **argv, int *rows, int *columns)
{
	char	*line;
	char	**split;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || rows == NULL || columns == NULL)
		return (-1);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), -1);
	(*rows) = 0;
	while (line)
	{
		split = ft_split(line, ' ');
		if (split == NULL)
		{
			close(fd);
			return (free(line), -1);
		}
		if ((*rows) == 0)
			(*columns) = st_len_split(split);
		else if (st_len_split(split) != (*columns))
		{
			close(fd);
			fdf_free_split(split);
			return (free(line), -1);
		}
		fdf_free_split(split);
		free(line);
		line = get_next_line(fd);
		(*rows)++;
	}
	return (close(fd), 0);
}
