/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:46:51 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/08/28 15:04:36 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int32_t	st_free_shell(t_fdf_map_info *map, t_fdf_image_info *image, t_fdf_data *data, char *message)
{
	if (map != NULL)
		free(map);
	if (image != NULL)
		free(image);
	if (data != NULL)
		free(data);
	ft_printf("Error: \t %s \n", message);
	exit(EXIT_FAILURE);
}

static t_fdf_map_info	*st_init_map_info(t_fdf_map_info *map, char **argv)
{
	int	columns;
	int	rows;
	int	check;
	int	***map_coord;

	columns = 0;
	rows = 0;
	check = fdf_counting_rows_and_columns(argv, &rows, &columns);
	if (check < 0 || map == NULL)
		return (NULL);
	map->rows = rows;
	map->columns = columns;
	map->size = rows * columns;
	map_coord = malloc(sizeof(int **));
	if (map_coord == NULL)
		return (NULL);
	(*map_coord) = malloc(rows * sizeof(int *));
	if (*map_coord == NULL)
		return (free(map_coord), NULL);
	check = fdf_allocate_array(map_coord, map);
	if (check < 0)
	{
		free(map_coord);
		return (free(*map_coord), NULL);
	}
	check = 0;
	check = fdf_init_coordinate_array(argv, map_coord, map);
	if (check < 0)
	{
		if (map_coord != NULL)
			fdf_free_int_array_until_j(map_coord, (map->rows), map);
		return (NULL);
	}
	map->map_coord = map_coord;
	return (map);
}

static t_fdf_image_info	*st_init_image_info(t_fdf_image_info *image)
{
	mlx_t	*mlx;
	mlx_image_t	*img;

	if (image == NULL)
		return (NULL);
	image->width = 2000;
	image->height = 1000;
	mlx = mlx_init((image->width), (image->height), "FDF????", true);
	if (!mlx)
		return (NULL);
	img = mlx_new_image(mlx, (image->width), (image->height));
	if (!img)
	{
		mlx_terminate(mlx);
		return (NULL);
	}
	image->img = img;
	image->mlx = mlx;
	return (image);
}

int32_t	fdf_init_data(t_fdf_data *data, char **argv)
{
	t_fdf_image_info	*image;
	t_fdf_image_info	*check_img;
	t_fdf_map_info		*map;
	t_fdf_map_info		*check_map;

	image = malloc(sizeof(t_fdf_image_info));
	map = malloc(sizeof(t_fdf_map_info));
	if (image == NULL || map == NULL || data == NULL)
		st_free_shell(map, image, data, "failed to allocate memory");
	check_img = st_init_image_info(image);
	if (check_img != image)
		st_free_shell(map, image, data, "failed to initialise window or image");
	check_map = st_init_map_info(map, argv);
	if (check_map != map)
		st_free_shell(map, image, data, "failed to initialise map information struct");
	data->image = image;
	data->map = map;
	return (0);
}
