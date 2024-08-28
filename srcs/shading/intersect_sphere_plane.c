/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere_plane.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:05:52 by gsims             #+#    #+#             */
/*   Updated: 2024/08/20 11:41:08 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Creates an intersect struct according to given sphere and ray in object space
static t_intersect	create_intersect_sphere(t_sphere *sphere, t_ray ray)
{
	t_tuple		dist;
	double		a;
	double		b;
	double		c;
	t_intersect	intersection;

	dist = subtr_tuple(ray.origin, create_tuple(0, 0, 0, POINT));
	a = dot_prod(ray.direction, ray.direction);
	b = 2 * dot_prod(ray.direction, dist);
	c = dot_prod(dist, dist) - (sphere->radius * sphere->radius);
	intersect_helper(a, b, c, &intersection);
	intersection.obj = sphere->obj;
	return (intersection);
}

// Creates an intersect struct according to given sphere and ray
// Transforms the ray into object space before creating the intersect
t_intersect	intersect_sphere(void *obj_ptr, t_ray ray)
{
	t_sphere	*sphere;
	t_ray		ray_obj_space;
	double		**inverted_trans_matrix;
	t_intersect	intersection;

	sphere = (t_sphere *)obj_ptr;
	inverted_trans_matrix = invert_matrix(sphere->obj->transformation_matrix);
	ray_obj_space = transform_ray(ray, inverted_trans_matrix);
	intersection = create_intersect_sphere(sphere, ray_obj_space);
	matrix_free(inverted_trans_matrix, 4);
	return (intersection);
}

// Creates an intersect struct according to given plane and ray in object space
static t_intersect	create_intersect_plane(t_plane *plane, t_ray ray)
{
	t_intersect	intersection;
	double		denom;
	double		t;
	t_tuple		p0_to_origin;

	intersection.intersected = false;
	intersection.t_value1 = DBL_MAX;
	intersection.t_value2 = DBL_MAX;
	denom = dot_prod(plane->normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		p0_to_origin = subtr_tuple(plane->point, ray.origin);
		t = dot_prod(p0_to_origin, plane->normal) / denom;
		if (t >= 0)
		{
			intersection.intersected = true;
			intersection.t_value1 = t;
			intersection.t_value2 = DBL_MAX;
		}
	}
	intersection.obj = plane->obj;
	return (intersection);
}

// Creates an intersect struct according to given plane and ray
// Transforms the ray into object space before creating the intersect
t_intersect	intersect_plane(void *obj_ptr, t_ray ray)
{
	t_plane		*plane;
	t_ray		ray_obj_space;
	double		**inverted_trans_matrix;
	t_intersect	intersection;

	plane = (t_plane *)obj_ptr;
	inverted_trans_matrix = invert_matrix(plane->obj->transformation_matrix);
	ray_obj_space = transform_ray(ray, inverted_trans_matrix);
	intersection = create_intersect_plane(plane, ray_obj_space);
	matrix_free(inverted_trans_matrix, 4);
	return (intersection);
}
