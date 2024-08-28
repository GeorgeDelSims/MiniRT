/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transformation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:09:55 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:09:56 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Creates a new_ray ray object based on given origin and direction
t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	new_ray;

	new_ray.origin = origin;
	new_ray.direction = direction;
	new_ray.intersection_array = NULL;
	new_ray.object = NULL;
	return (new_ray);
}

// Determines the position point on a ray at a given time (=t) or distance
t_tuple	position(t_ray ray, double time)
{
	t_tuple	pos;

	pos.x = ray.origin.x + (ray.direction.x * time);
	pos.y = ray.origin.y + (ray.direction.y * time);
	pos.z = ray.origin.z + (ray.direction.z * time);
	return (pos);
}

// Transform a ray by multiplying its origin and its direction
// by a transformation matrix
t_ray	transform_ray(t_ray ray, double **matrix)
{
	t_ray	new_ray;

	new_ray.origin = matrix_point_mul(matrix, ray.origin);
	new_ray.direction = matrix_vect_mul(matrix, ray.direction);
	return (new_ray);
}
