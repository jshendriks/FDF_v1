/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   src.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:22:30 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/01 15:32:18 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef SRC_H
# define SRC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sysexits.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "MLX42.h"
# include "./../src/libs/libft/include/libft.h"

typedef struct s_fdf_bresenham
{
	float	dx;
	float	dy;
	int		sign_dx;
	int		sign_dy;
	float	eps;
}	t_fdf_bresenham;

typedef struct s_fdf_image_info
{
	int	width;
	int	height;
	mlx_image_t	*img;
	mlx_t		*mlx;
}	t_fdf_image_info;

typedef struct s_fdf_map_info
{
	int	size;
	int	columns;
	int	rows;
	int	***map_coord;
}	t_fdf_map_info;

typedef struct s_fdf_data
{
	t_fdf_image_info	*image;
	t_fdf_map_info		*map;
}	t_fdf_data;

typedef struct s_fdf_vec
{
	float	x;
	float	y;
}	t_fdf_vec;

//FUNCTIONS FOR PARSING -----------------------------------------------------------------
int	fdf_arg_check(int argc, char **argv);
int32_t	fdf_init_data(t_fdf_data *data, char **argv);
int	fdf_init_coordinate_array(char **argv, int ***map_coord, t_fdf_map_info *map);
int	fdf_atoi_overflw(const char *str, int *ptr_num);
int	fdf_set_rows_and_columns(char **argv, int *rows, int *columns);
int	fdf_allocate_array(int ***map_coord, t_fdf_map_info *map);

//FUNCTIONS TO FREE ---------------------------------------------------------------------
void	fdf_free_int_array_until_j(int ***map_coord, int j, t_fdf_map_info *map);
void	fdf_free_split(char **ptr_subs);
void	fdf_terminate_map_info(t_fdf_map_info *map);
void	fdf_terminate_image_info(t_fdf_image_info *image);
void	fdf_terminate_data_struct(t_fdf_data **data);

//FUNCTIONS TO CALCULATE ----------------------------------------------------------------
void	fdf_isometric_projection(t_fdf_vec *vec, int x, int y, int z);
float	fdf_abs_fl(float nb);
float	fdf_max_x_value(t_fdf_data *data, float scale, int indicator);
float	fdf_min_x_value(t_fdf_data *data, float scale, int indicator);
float	fdf_max_y_value(t_fdf_data *data, float scale, int indicator);
float	fdf_min_y_value(t_fdf_data *data, float scale, int indicator);

//FUNCTIONS TO DRAW LINES ---------------------------------------------------------------
void	fdf_draw_lines(t_fdf_data *data);
void	fdf_vertical_line(t_fdf_vec vec_from, t_fdf_vec vec_to, t_fdf_data *data);
void	fdf_horizontal_line(t_fdf_vec vec_from, t_fdf_vec vec_to, t_fdf_data *data);
void	fdf_bresenham_line(t_fdf_vec vec_from, t_fdf_vec vec_to, t_fdf_data *data);
void	fdf_scale(t_fdf_vec *vec1, float scale);
void	fdf_translate(t_fdf_vec *vec1, float translation_x, float translation_y);
float	fdf_get_scale(t_fdf_data *data);
float	fdf_get_x_translation(t_fdf_data *data, float scale);
float	fdf_get_y_translation(t_fdf_data *data, float scale);

//FUNCTIONS TO TEST WITH -----------------------------------------------------------------
void	fdf_print_array(t_fdf_map_info *map);
void	fdf_print_image_info(t_fdf_image_info *image);
void	fdf_print_map_info(t_fdf_map_info *map);
void	fdf_print_data(t_fdf_data *data);

#endif
