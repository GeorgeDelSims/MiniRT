/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:48:53 by gsims             #+#    #+#             */
/*   Updated: 2024/08/24 19:42:00 by rtauzin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define VECT 0.0
# define POINT 1.0
# define BUFFER_SIZE 1
# define SPHERE 0
# define CYLINDER 1
# define PLANE 2
# define HEIGHT 600
# define WIDTH 800
# define EPSILON 1e-6

// ANSI colour codes for coloured output
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

// Number of attributs for each element
# define NB_ATR_AMBIENT 2
# define NB_ATR_CAMERA 3
# define NB_ATR_LIGHT 3
# define NB_ATR_SPHERE 3
# define NB_ATR_PLANE 3
# define NB_ATR_CYLINDER 5

// Forward declarations
typedef struct s_tuple			t_tuple;
typedef struct s_color			t_color;
typedef struct s_intersect		t_intersect;
typedef struct s_ray			t_ray;
typedef struct s_scene			t_scene;
typedef struct s_object			t_object;
typedef struct s_material		t_material;
typedef struct s_light_source	t_light;

// Define the function pointer type for intersection functions
typedef t_intersect				(*t_intersect_func)(void *object, t_ray ray);

// material characteristics of each object
typedef struct s_material
{
	double						ambient;
	double						diffuse;
	double						specular;
	double						shininess;
}								t_material;

// img struct for mlx lib
typedef struct s_img
{
	void						*img;
	char						*addr;
	int							bits_per_pixel;
	int							line_length;
	int							endian;
}								t_img;

// tuple = vector or point
// (x, y, z) coordinates and type is 1.0 for a point and 0.0 for a vector
typedef struct s_tuple
{
	double						x;
	double						y;
	double						z;
	double						type;
}								t_tuple;

// Camera struct (with transformation matrix for changing orientation)
typedef struct s_camera
{
	double						hsize;
	double						vsize;
	double						fov;
	double						**trans;
	double						pixel_size;
	double						half_width;
	double						half_height;
	t_tuple						origin;
	t_tuple						orientation;
}								t_camera;

// Color of objects
typedef struct s_color
{
	double						red;
	double						green;
	double						blue;
}								t_color;

typedef struct s_phong
{
	t_color						ambient;
	t_color						diffuse;
	t_color						specular;
	t_color						effective_color;
	t_tuple						reflect_vect;
	t_tuple						normal_vect;
	t_tuple						light_vect;
}								t_phong;

// intersection between ray and object
// will contain more values later
typedef struct s_intersect
{
	bool						intersected;
	double						t_value1;
	double						t_value2;
	t_object					*obj;
}								t_intersect;

typedef struct s_ray
{
	t_tuple						origin;
	t_tuple						direction;
	t_intersect					*intersection_array;
	t_object					*object;
	t_tuple						point;
}								t_ray;

// Light source
typedef struct s_light_source
{
	t_tuple						position;
	double						brightness;
	t_color						intensity;
}								t_light;

// ambient lightning
typedef struct s_ambient
{
	double						ambient_light;
	t_color						color;
}								t_ambient;

// Scene (main data structure)
typedef struct s_scene
{
	char						*rt_file;
	t_object					*objects;
	int							object_count;
	void						*mlx;
	void						*win;
	t_light						light_source;
	t_camera					camera;
	t_ambient					ambient;
	int							width;
	int							height;
}								t_scene;

// Objects such as spheres, cylindres and rectangles
typedef struct s_object
{
	int							id;
	int							type;
	void						*ptr;
	t_intersect_func			intersect_func;
	t_material					material;
	t_color						color;
	double						**transformation_matrix;
}								t_object;

// SPHERE OBJECT
typedef struct s_sphere
{
	t_object					*obj;
	int							id;
	t_tuple						centre;
	double						diameter;
	double						radius;
	t_color						color;
}								t_sphere;

// PLANE OBJECT
typedef struct s_plane
{
	t_object					*obj;
	int							id;
	t_tuple						point;
	t_tuple						normal;
	t_color						color;
}								t_plane;

// CYLINDER OBJECT
typedef struct s_cylinder
{
	t_object					*obj;
	int							id;
	t_tuple						centre;
	t_tuple						orientation;
	bool						closed;
	double						min;
	double						max;
	double						diameter;
	double						radius;
	double						height;
	t_color						color;
}								t_cylinder;

/* ---------- TUPLE ARITHMETIC ---------- */

t_tuple							create_tuple(double x, double y, double z,
									double type);
t_tuple							add_tuple(t_tuple v1, t_tuple v2);
t_tuple							subtr_tuple(t_tuple v1, t_tuple v2);
t_tuple							negate_tuple(t_tuple vector);
t_tuple							scale_tuple(t_tuple vector, double scalar);
t_tuple							div_tuple(t_tuple vector, double scalar);
double							magnitude(t_tuple vect);
t_tuple							normalise(t_tuple vector);
double							dot_prod(t_tuple v1, t_tuple v2);
t_tuple							cross_prod(t_tuple v1, t_tuple v2);
void							print_tuple(t_tuple tup);
double							double_sqrt(double a);

/* ---------- MATRIX UTILS ---------- */

// matrix.c
void							matrix_free(double **matrix, size_t size);
void							print_matrix(double **matrix, size_t size,
									char *name);
bool							matrix_equal(double **m1, double **m2,
									size_t size);
void							free_matrix(double **matrix, size_t size);

// matrix_create.c
double							**matrix_alloc(size_t size);
double							**fill_matrix(double value, size_t size);
double							**test_matrix(double value, size_t size);
double							**identity_matrix(size_t size);

// matrix_ops.c
double							**matrix_mul(double **m1, double **m2);
double							**matrix_transpose(double **matrix);
double							**transpose_3x3(double **matrix);
double							**scalar_div(double **matrix, double div,
									size_t size);
double							**scalar_mul(double **matrix, double mul,
									size_t size);

// matrix_tuple_ops.c
double							**trans_3x3(double **matrix);
t_tuple							matrix_vect_mul_3x3(double **m, t_tuple v);
t_tuple							matrix_point_mul_4x4(double **m, t_tuple p);
t_tuple							matrix_point_mul(double **m, t_tuple p);
t_tuple							matrix_vect_mul(double **m, t_tuple v);

// submatrix.c
double							**submatrix(double **matrix, size_t row,
									size_t col, size_t size);

// determinants.c
double							determinant_2x2(double **m);
double							determinant3x3(double **matrix);
double							determinant4x4(double **matrix);
double							minor3x3(double **matrix, size_t row,
									size_t col);
double							minor4x4(double **matrix, size_t row,
									size_t col);

// cofactors.c
double							cofactor3x3(double **matrix, size_t row,
									size_t col);
double							cofactor4x4(double **matrix, size_t row,
									size_t col);
double							**cofactor_matrix(double **matrix);

// invert.c
bool							is_invertible(double **matrix);
double							**invert_matrix(double **matrix);

// mlx_utils.c
void							write_pixel(t_img *img, int x, int y,
									int colour);

/* ---------- TRANSFORMATIONS ---------- */

// translation.c
double							**init_matrix_scalandtransl(t_object *obj);
double							**translation_matrix(double x, double y,
									double z);
double							**create_scaling_matrix_sphere(t_object *obj);
double							**scaling_matrix(double x, double y, double z);

// rotation.c
double							**build_rotation_matrix(t_tuple current_dir,
									t_tuple target_dir);

// ray_transformation.c
t_ray							create_ray(t_tuple origin, t_tuple direction);
t_tuple							position(t_ray ray, double time);
t_ray							transform_ray(t_ray ray, double **matrix);

// objects.c
void							ft_init_obj(t_scene *scene, char **data,
									int type, int index);

// intersection_functions.c
t_intersect						*intersect_array(t_scene *scene, t_ray ray);
double							get_hit(t_ray *ray, int count);
void							intersect_helper(double a, double b, double c,
									t_intersect *intersection);

// intersect_sphere_plane.c
t_intersect						intersect_plane(void *obj_ptr, t_ray ray);
t_intersect						intersect_sphere(void *object, t_ray ray);

// intersect_cyl.c
t_intersect						intersect_cylinder(void *obj_ptr, t_ray ray);

// intersect_cyl_caps.c
void							intersect_caps(t_cylinder *cyl, t_ray ray,
									t_intersect *intersection);

// object_transformation.c
void							apply_trans_matrix_sphere(t_sphere *sphere);
void							apply_trans_matrix_plane(t_plane *plane);
void							apply_trans_matrix_cyl(t_cylinder *cyl);

/* ---------- SHADING ---------- */

// normal.c
t_tuple							world_normal_sphere(t_object *object,
									t_tuple world_point);
t_tuple							world_normal_cylinder(t_object *object,
									t_tuple point);

// reflect.c
t_tuple							reflect(t_tuple in, t_tuple normal);

// material.c
void							set_default_material(t_object *object);
t_color							combine_color(t_color intensity, double scalar);
t_color							combine_color_two(t_color intensity,
									double scalar1, double scalar2);
t_color							apply_mat_properties(t_color intensity,
									t_object *object);

// light.c
t_light							create_light_source(t_tuple position,
									t_color intensity);

// phong.c
t_color							phong_lighting(t_ray *ray, t_scene *scene,
									t_tuple eye_vect, double dot);

// color.c
t_color							create_color(double r, double g, double b);
int								col_to_int(t_color color);
void							print_color(t_color color);
t_color							combine_shading(t_color amb, t_color diff,
									t_color spec, bool shadow);
t_color							add_scalar_to_color(t_color color,
									double scalar);
t_color							mul_scalar_with_color(t_color color,
									double scalar);

// shadow.c
bool							is_shadow(t_scene *scene, t_tuple point);

/* ---------- PARSING ---------- */
t_scene							ft_alloc_scene(t_scene *scene);
void							ft_open_file_rt(t_scene *scene, char *rt_file);
char							*ft_get_next_line(int fd);
void							ft_clean_file_rt(t_scene *scene);
t_scene							ft_parsing_rt(t_scene *scene);
void							advance_through_number(char **tmp_ptr);
int								count_objects(char *rt_file);
void							parse_object(t_scene *scene, char **tmp,
									int *index_obj);
void							parse_scene_element(t_scene *scene, char **tmp);
void							check_first_element(char **tmp, t_scene *scene);

// parsing_misconfiguration.c
void							check_misconfiguration_rt_file(t_scene *scene);
int								check_nb_objects(char *rt_file);
int								check_nb_elements(char *rt_file);

// parsing_checkdata.c
int								is_valid_format(char *str, char *id);
int								check_isdigit(char c);
int								check_valid_digit(char *str);
int								is_separator(char *str);

//  parsing_checkdata2.c
void							check_valid_ambient_lighting(char *str);
void							check_valid_fov(char *str);
void							check_valid_brightness(char *str);
void							check_valid_center(char *str);
void							check_valid_vector(char *str);

// parsing_checkdatav3.c
int								check_valid_param(int param_accepted,
									int param_count);
int								is_new_element(char *str);
void							check_valid_diameter(char *str);
void							advance_through_number(char **tmp_ptr);
int								is_wrong_float(char *str);

// parsing_checkdatav4.c
void							validate_color_value(int color);
void							check_consecutive_commas(char *str, int i);
void							check_comma_count(int commacount);
void							check_valid_color(char *str);

// parsing_checkdatav5.c
void							check_orientation_range(float orient);
int								is_invalid_coordinate(char *str, int i);
int								check_comma(char *str, int i, int *commacount);

// parsing_checkambient.c
void							validate_element(char *tmp_ptr,
									t_ambient *ambient, t_scene *scene);
void							check_ambient_allocation(t_ambient *ambient,
									t_scene *scene);
void							insert_ambiantparam_or_exit(int param,
									t_ambient *ambient, char **tmp_ptr,
									t_scene *scene);
void							validate_ambiant_new_element(char *tmp_ptr,
									t_ambient *ambient, t_scene *scene);
void							check_ambiantparam_or_exit(int actual,
									t_ambient *ambient, char *tmp_ptr,
									t_scene *scene);

// parsing_checkcamera.c
void							check_cameraparam_or_exit(int actual,
									t_camera *camera, char *tmp_ptr,
									t_scene *scene);
void							insert_cameraparam_or_exit(int param,
									t_camera *camera, char **tmp_ptr,
									t_scene *scene);
void							validate_camera_new_element(char *tmp_ptr,
									t_camera *camera, t_scene *scene);
void							check_camera_allocation(t_camera *camera,
									t_scene *scene);

// parsing_checklight.c
void							check_lightparam_or_exit(int actual,
									t_light *light, char *tmp_ptr,
									t_scene *scene);
void							insert_lightparam_or_exit(int param,
									t_light *light, char **tmp_ptr,
									t_scene *scene);
void							validate_light_new_element(char *tmp_ptr,
									t_light *light, t_scene *scene);
void							check_light_allocation(t_light *light,
									t_scene *scene);

// parsing_checksphere.c
void							check_sphereparam_or_exit(int actual,
									t_sphere *sphere, char *tmp_ptr,
									t_scene *scene);
void							insert_sphereparam_or_exit(int param,
									t_sphere *sphere, char **tmp_ptr,
									t_scene *scene);
void							validate_sphere_new_element(char *tmp_ptr,
									t_sphere *sphere, t_scene *scene);
void							check_sphere_allocation(t_sphere *sphere,
									t_scene *scene);

// parsing_checkplane.c
void							check_planeparam_or_exit(int actual,
									t_plane *plane, char *tmp_ptr,
									t_scene *scene);
void							insert_planeparam_or_exit(int param,
									t_plane *plane, char **tmp_ptr,
									t_scene *scene);
void							validate_plane_new_element(char *tmp_ptr,
									t_plane *plane, t_scene *scene);
void							check_plane_allocation(t_plane *plane,
									t_scene *scene);

// parsing_checkcylinder.c
void							check_cylinderparam_or_exit(int actual,
									t_cylinder *cylinder, char *tmp_ptr,
									t_scene *scene);
void							insert_cylinderparam_or_exit(int param,
									t_cylinder *cylinder, char **tmp_ptr,
									t_scene *scene);
void							validate_cylinder_new_element(char *tmp_ptr,
									t_cylinder *cylinder, t_scene *scene);
void							check_cylinder_allocation(t_cylinder *cylinder,
									t_scene *scene);

// parsing_utils.c
void							free_all_objects(t_scene *scene);
void							free_object(t_object *obj);

// parsing_utils2.c
int								parse_color_params(t_color *color,
									char **tmp_ptr);
int								parse_centre_params(t_tuple *vect,
									char **tmp_ptr);

// parsing_sphere.c
t_sphere						*sphere(t_scene *scene, t_object *obj,
									char *tmp);
void							ft_create_sphere(t_scene *scene, t_object *obj,
									char **tmp);
int								insert_sphere_param(int param, t_sphere *sphere,
									char **tmp_ptr);
int								parse_sphere_params(t_sphere *sphere,
									char *tmp);
int								ft_insert_centre(t_tuple *vect, char **tmp_ptr);
int								ft_insert_diameter(t_sphere *diameter,
									char **tmp_ptr);
int								ft_insert_color(t_color *color, char **tmp_ptr);

// parsing_camera.c
t_scene							ft_insert_camera(t_scene *scene, char **tmp);
int								insert_camera_param(int param, t_camera *camera,
									char **tmp_ptr);
int								ft_insert_fov(t_camera *camera, char **tmp_ptr);
int								ft_insert_vector(t_tuple *vect, char **tmp_ptr);

// parsing_light.c
t_scene							ft_insert_light(t_scene *scene, char **tmp);
int								insert_light_param(int param, t_light *light,
									char **tmp_ptr);

// parsing_ambient.c
t_scene							ft_insert_ambient(t_scene *scene, char **tmp);
int								insert_ambient_param(int param,
									t_ambient *ambient, char **tmp_ptr);

// parsing_plane.c
void							create_plane(t_scene *scene, t_object *obj,
									char **tmp, int index);
int								insert_plane_param(int param, t_plane *plane,
									char **tmp_ptr);
t_plane							*init_plane(t_scene *scene, t_object *obj,
									char *tmp);

// parsing_cylinder.c
int								parse_cylinder_params(t_cylinder *cylinder,
									char **tmp);
void							create_cylinder(t_scene *scene, t_object *obj,
									char **tmp);
int								insert_cylinder_param(int param,
									t_cylinder *cylinder, char **tmp_ptr);

/* ---------- ERROR HANDLING ---------- */
int								ft_error_nb_arg(void);
int								ft_check_args(int argc, char **argv);
int								ft_error_open_file(void);
int								ft_error_file_empty(void);
void							check_allocation(t_scene *scene);

/* ---------- LIBFT ---------- */
int								ft_strncmp(char *s1, char *s2, size_t n);
void							*ft_memmove(void *dst, const void *src,
									size_t len);
char							*ft_substr(char const *str, unsigned int start,
									size_t len);
size_t							ft_strlen(const char *str);
char							*ft_strchr(const char *str, char c);
char							*ft_strdup(const char *str);
char							*ft_strjoin(char const *s1, char const *s2);
double							ft_atof(char *str);
int								ft_atoi(const char *str);

/* ---------- WINDOW ---------- */

void							ft_init_scene(t_scene *scene, int width,
									int height, int number_of_objects);
void							cast_rays(t_scene *scene);

// camera.c
t_camera						compute_camera_values(t_camera camera,
									double hsize, double vsize, double fov);
double							**view_transform(t_tuple from, t_tuple to);
double							deg_to_rad(double degrees);

/* ---------- MLX ---------- */
void							exit_program(t_scene *scene);
int								key_hook(int keycode, t_scene *scene);

#endif
