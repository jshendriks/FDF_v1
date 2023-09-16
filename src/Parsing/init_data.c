/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:46:51 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/16 16:11:41 by jagna         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "src.h"

static int32_t	st_free(t_map_inf *map, t_img_inf *img, t_data *data, char *s)
{
	if (map != NULL)
		free(map);
	if (img != NULL)
		free(img);
	if (data != NULL)
		free(data);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

static int	st_alloc_init_mapar(t_map_inf *map, int ***co_map, char **argv)
{
	int	check;

	(*co_map) = malloc((map->rows) * sizeof(int *));
	if (*co_map == NULL)
		return (free(co_map), -1);
	check = fdf_allocate_array(co_map, map);
	if (check < 0)
		return (free(co_map), -1);
	check = 0;
	check = fdf_init_coord_array(argv, co_map, map);
	if (check < 0)
	{
		if (*co_map != NULL)
			fdf_free_int_array_until_j(co_map, (map->rows), map);
		return (free(co_map), -1);
	}
	return (0);
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
	check = st_alloc_init_mapar(map, map_coord, argv);
	if (check < 0)
		return (NULL);
	map->map_coord = map_coord;
	return (map);
}

static t_img_inf	*st_init_image_info(t_img_inf *image, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (image == NULL)
		return (NULL);
	image->width = 900;
	image->height = 900;
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
	t_map_inf	*map;
	t_map_inf	*check_map;

	image = malloc(sizeof(t_img_inf));
	map = malloc(sizeof(t_map_inf));
	if (image == NULL || map == NULL || data == NULL)
		st_free(map, image, data, "Allocating memory failed");
	check_img = st_init_image_info(image, argv);
	if (check_img != image)
		st_free(map, image, data, "Initialising image struct failed");
	check_map = st_init_map_info(map, argv);
	if (check_map != map)
		st_free(map, image, data, "Initialising map struct failed");
	data->image = image;
	data->map = map;
	return (0);
}
