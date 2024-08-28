/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cyl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:05:49 by gsims             #+#    #+#             */
/*   Updated: 2024/08/20 12:01:02 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// in the case of a ray that is parallel to the cyl,
// check if intersect is within y bounds
static void	intersect_within_bounds(t_cylinder *cyl, t_ray ray,
		t_intersect *intersection)
{
	double	y1;
	double	y2;

	y1 = ray.origin.y + intersection->t_value1 * ray.direction.y;
	y2 = ray.origin.y + intersection->t_value2 * ray.direction.y;
	if (y1 < cyl->min || y1 > cyl->max)
		intersection->t_value1 = DBL_MAX;
	if (y2 < cyl->min || y2 > cyl->max)
		intersection->t_value2 = DBL_MAX;
	if (intersection->t_value1 < DBL_MAX || intersection->t_value2 < DBL_MAX)
		intersection->intersected = true;
}

// says it in the name
static t_intersect	ray_is_parallel_to_cyl(t_cylinder *cyl,
		t_intersect intersection)
{
	if (cyl->closed == false)
	{
		intersection.intersected = false;
		intersection.t_value1 = DBL_MAX;
		intersection.t_value2 = DBL_MAX;
		return (intersection);
	}
	else
		return (intersection);
}

// Creates an intersect according to the given cyl and ray in obj space
static t_intersect	create_intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	t_intersect	intersection;
	double		a;
	double		b;
	double		c;

	intersection.intersected = false;
	intersection.t_value1 = DBL_MAX;
	intersection.t_value2 = DBL_MAX;
	a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	b = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z);
	c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - cyl->radius
		* cyl->radius;
	if (fabs(a) < EPSILON)
		return (ray_is_parallel_to_cyl(cyl, intersection));
	else
	{
		intersect_helper(a, b, c, &intersection);
		intersect_within_bounds(cyl, ray, &intersection);
	}
	if (cyl->closed == true)
		intersect_caps(cyl, ray, &intersection);
	intersection.obj = cyl->obj;
	return (intersection);
}

// Creates an intersect struct according to the given cyl and ray
// Transforms the ray into object space before creating the intersect
t_intersect	intersect_cylinder(void *obj_ptr, t_ray ray)
{
	t_cylinder	*cyl;
	t_ray		ray_obj_space;
	double		**inverted_trans_matrix;
	t_intersect	intersection;

	cyl = (t_cylinder *)obj_ptr;
	inverted_trans_matrix = invert_matrix(cyl->obj->transformation_matrix);
	ray_obj_space = transform_ray(ray, inverted_trans_matrix);
	matrix_free(inverted_trans_matrix, 4);
	intersection = create_intersect_cylinder(cyl, ray_obj_space);
	return (intersection);
}
