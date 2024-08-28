/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:05:55 by gsims             #+#    #+#             */
/*   Updated: 2024/08/20 12:04:58 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// intersection helper function
void	intersect_helper(double a, double b, double c,
		t_intersect *intersection)
{
	double	discriminant;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
	{
		intersection->intersected = false;
		intersection->t_value1 = DBL_MAX;
		intersection->t_value2 = DBL_MAX;
	}
	else if (discriminant == 0)
	{
		intersection->intersected = true;
		intersection->t_value1 = (-b) / (2 * a);
		intersection->t_value2 = DBL_MAX;
	}
	else if (discriminant > 0)
	{
		intersection->intersected = true;
		intersection->t_value1 = (-b - sqrt(discriminant)) / (2 * a);
		intersection->t_value2 = (-b + sqrt(discriminant)) / (2 * a);
	}
}

// Creates an array of all potential intersections
// between the ray and all objects in the scene
t_intersect	*intersect_array(t_scene *scene, t_ray ray)
{
	int			i;
	t_object	*obj;

	ray.intersection_array = malloc(sizeof(t_intersect) * (scene->object_count
				+ 1));
	if (!ray.intersection_array)
		return (NULL);
	i = 0;
	while (i < scene->object_count)
	{
		obj = &scene->objects[i];
		if (obj->intersect_func)
			ray.intersection_array[i] = obj->intersect_func(obj->ptr, ray);
		else
			printf("Error: intersect_func not initialized for object %d\n", i);
		i++;
	}
	return (ray.intersection_array);
}

// Function identifying the first hit in an array of intersections
// the first hit will be the intersection with the smallest positive t_value
// Returns -1 in the case of no hits or only negative hits
double	get_hit(t_ray *ray, int count)
{
	int			i;
	double		hit;
	t_intersect	*array;

	array = ray->intersection_array;
	i = 0;
	hit = DBL_MAX;
	while (i < count)
	{
		if (array[i].t_value1 > 0 && array[i].t_value1 < hit)
		{
			hit = array[i].t_value1;
			ray->object = array[i].obj;
		}
		if (array[i].t_value2 > 0 && array[i].t_value2 < hit)
		{
			hit = array[i].t_value2;
			ray->object = array[i].obj;
		}
		i++;
	}
	if (hit == DBL_MAX)
		return (-1);
	return (hit);
}

/*
	World Space vs Object space :
	Another way to think about transformation matrices
	is to think of them as converting points between
	two different coordinate systems.

	At the scene or world level, everything is in world space coordinates,
	relative to the overall world. (the centre of the SCENE is the origin)

	But at the object level, everything is in object space coordinates,
	relative to the object itself. (the centre of the OBJECT is the origin)
*/
