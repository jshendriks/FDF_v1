/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   src.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 11:22:30 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/04 20:38:39 by jagna         ########   odam.nl         */
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

typedef struct s_bresenham
{
	float	dx;
	float	dy;
	int		sign_dx;
	int		sign_dy;
	float	eps;
}	t_bresenham;

typedef struct s_img_inf
{
	int	width;
	int	height;
	mlx_image_t	*img;
	mlx_t		*mlx;
}	t_img_inf;

typedef struct s_map_inf
{
	int	size;
	int	columns;
	int	rows;
	int	***map_coord;
}	t_map_inf;

typedef struct s_data
{
	t_img_inf	*image;
	t_map_inf		*map;
}	t_data;

typedef struct s_vec
{
	float	x;
	float	y;
}	t_vec;

typedef struct s_crit
{
		int	y;
		int	indicator;
		float	scale;
}	t_crit;

//FUNCTIONS FOR PARSING -----------------------------------------------------------------
int	fdf_arg_check(int argc, char **argv);
int32_t	fdf_init_data(t_data *data, char **argv);
int	fdf_init_coordinate_array(char **argv, int ***map_coord, t_map_inf *map);
int	fdf_atoi_overflw(const char *str, int *ptr_num);
int	fdf_set_rows_and_columns(char **argv, int *rows, int *columns);
int	fdf_allocate_array(int ***map_coord, t_map_inf *map);

//FUNCTIONS TO FREE ---------------------------------------------------------------------
void	fdf_free_int_array_until_j(int ***map_coord, int j, t_map_inf *map);
void	fdf_free_split(char **ptr_subs);
void	fdf_terminate_map_info(t_map_inf *map);
void	fdf_terminate_image_info(t_img_inf *image);
void	fdf_terminate_data_struct(t_data **data);

//FUNCTIONS TO CALCULATE ----------------------------------------------------------------
void	fdf_isometric_projection(t_vec *vec, int x, int y, int z);
float	fdf_abs_fl(float nb);
float	fdf_max_x_value(t_data *data, float scale, int indicator);
float	fdf_min_x_value(t_data *data, float scale, int indicator);
float	fdf_max_y_value(t_data *data, float scale, int indicator);
float	fdf_min_y_value(t_data *data, float scale, int indicator);

//FUNCTIONS TO DRAW LINES ---------------------------------------------------------------
void	fdf_draw_lines(t_data *data);
void	fdf_vertical_line(t_vec vec_from, t_vec vec_to, t_data *data);
void	fdf_horizontal_line(t_vec vec_from, t_vec vec_to, t_data *data);
void	fdf_bresenham_line(t_vec vec_from, t_vec vec_to, t_data *data);
void	fdf_scale(t_vec *vec1, float scale);
void	fdf_translate(t_vec *vec1, float translation_x, float translation_y);
float	fdf_get_scale(t_data *data);
float	fdf_get_x_translation(t_data *data, float scale);
float	fdf_get_y_translation(t_data *data, float scale);

//FUNCTIONS TO TEST WITH -----------------------------------------------------------------
void	fdf_print_array(t_map_inf *map);
void	fdf_print_image_info(t_img_inf *image);
void	fdf_print_map_info(t_map_inf *map);
void	fdf_print_data(t_data *data);

#endif
