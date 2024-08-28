/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:14:09 by gsims             #+#    #+#             */
/*   Updated: 2024/08/26 17:45:15 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Initiates MLX image into the s struct
void	init_img(t_scene *s)
{
	t_img	img;

	if (!s || !s->mlx || !s->win)
	{
		printf("Scene or MLX not properly initialized.\n");
		return ;
	}
	img.img = mlx_new_image(s->mlx, s->width, s->height);
	if (!img.img)
	{
		printf("Failed to create new image.\n");
		return ;
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
}

// creates a ray and calculates its intersections with objects in the s
t_ray	project_ray_from_camera(t_camera *camera, double px, double py)
{
	t_tuple	origin;
	t_tuple	pixel;
	t_tuple	direction_vect;
	double	world_x;
	double	world_y;

	world_x = camera->half_width - (px + 0.5) * camera->pixel_size;
	world_y = camera->half_height - (py + 0.5) * camera->pixel_size;
	pixel = matrix_point_mul(camera->trans, create_tuple(world_x, world_y, -1,
				POINT));
	origin = matrix_point_mul(camera->trans, create_tuple(0, 0, 0, POINT));
	direction_vect = normalise(subtr_tuple(pixel, origin));
	return (create_ray(origin, direction_vect));
}

// gets shading / colour for each pixel in world space
// checks that the intersection is not inside the object
static t_color	get_shading(t_scene *s, t_ray ray, double hit)
{
	t_tuple	eye_vect;
	t_color	col;
	t_tuple	normal_vect;
	double	dot;

	ray.direction = normalise(ray.direction);
	ray.point = position(ray, hit);
	eye_vect = negate_tuple(ray.direction);
	if (ray.object->type == PLANE)
		normal_vect = ((t_plane *)(ray.object->ptr))->normal;
	else if (ray.object->type == CYLINDER)
		normal_vect = world_normal_cylinder(ray.object, ray.point);
	else
		normal_vect = world_normal_sphere(ray.object, ray.point);
	ray.point = add_tuple(ray.point, scale_tuple(normal_vect, EPSILON / 2));
	dot = dot_prod(normal_vect, eye_vect);
	col = phong_lighting(&ray, s, eye_vect, dot);
	return (col);
}

// Function loops over every pixel of the image,
// casting a ray for each of them and checking intersections
void	cast_rays(t_scene *s)
{
	int		x;
	int		y;
	double	hit;
	t_ray	ray;
	t_color	col;

	y = 0;
	while (y < s->height - 1)
	{
		x = 0;
		while (x < s->width - 1)
		{
			ray = project_ray_from_camera(&s->camera, x, y);
			ray.intersection_array = intersect_array(s, ray);
			hit = get_hit(&ray, s->object_count);
			free(ray.intersection_array);
			if (hit >= 0 && hit < DBL_MAX)
			{
				col = get_shading(s, ray, hit);
				mlx_pixel_put(s->mlx, s->win, x, y, col_to_int(col));
			}
			x++;
		}
		y++;
	}
}
