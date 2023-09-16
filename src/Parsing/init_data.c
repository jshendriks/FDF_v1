/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:46:51 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/16 15:46:43 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int32_t	st_free_shell(t_map_inf *map, t_img_inf *image, t_data *data, char *message)
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

static t_map_inf	*st_init_map_info(t_map_inf *map, char **argv)
{
	int	columns;
	int	rows;
	int	check;
	int	***map_coord;

	columns = 0;
	rows = 0;
	check = fdf_set_rows_and_columns(argv, &rows, &columns);
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
		free(*map_coord);
		return (free(map_coord), NULL);
	}
	check = 0;
	check = fdf_init_coord_array(argv, map_coord, map);
	if (check < 0)
	{
		if (map_coord != NULL)
			fdf_free_int_array_until_j(map_coord, (map->rows), map);
		return (free(map_coord), NULL);
	}
	map->map_coord = map_coord;
	return (map);
}

static t_img_inf	*st_init_image_info(t_img_inf *image, char **argv)
{
	mlx_t	*mlx;
	mlx_image_t	*img;

	if (image == NULL)
		return (NULL);
	image->width = 1000;
	image->height = 1000;
	mlx = mlx_init((image->width), (image->height), argv[1], true);
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

int32_t	fdf_init_data(t_data *data, char **argv)
{
	t_img_inf	*image;
	t_img_inf	*check_img;
	t_map_inf		*map;
	t_map_inf		*check_map;

	image = malloc(sizeof(t_img_inf));
	map = malloc(sizeof(t_map_inf));
	if (image == NULL || map == NULL || data == NULL)
		st_free_shell(map, image, data, "failed to allocate memory");
	check_img = st_init_image_info(image, argv);
	if (check_img != image)
		st_free_shell(map, image, data, "failed to initialise window or image");
	check_map = st_init_map_info(map, argv);
	if (check_map != map)
		st_free_shell(map, image, data, "failed to initialise map information struct");
	data->image = image;
	data->map = map;
	return (0);
}
