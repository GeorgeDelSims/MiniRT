/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:06:03 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:06:04 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Get the normal vector of the given sphere in the world space
t_tuple	world_normal_sphere(t_object *object, t_tuple world_point)
{
	t_tuple	obj_p;
	t_tuple	obj_norm;
	t_tuple	world_norm_v;
	double	**inverse_m;
	double	**transposed_m;

	inverse_m = invert_matrix(object->transformation_matrix);
	transposed_m = trans_3x3(inverse_m);
	obj_p = matrix_point_mul_4x4(inverse_m, world_point);
	obj_norm = normalise(subtr_tuple(obj_p, create_tuple(0, 0, 0, POINT)));
	world_norm_v = normalise(matrix_vect_mul_3x3(transposed_m, obj_norm));
	matrix_free(transposed_m, 3);
	matrix_free(inverse_m, 4);
	return (world_norm_v);
}

// Helper function to offload variables from cyl function
static t_tuple	get_world_norm(double **inverse_m, t_tuple obj_norm)
{
	double	**transposed_m;
	t_tuple	world_norm_v;

	transposed_m = trans_3x3(inverse_m);
	world_norm_v = normalise(matrix_vect_mul_3x3(transposed_m, obj_norm));
	matrix_free(transposed_m, 3);
	return (world_norm_v);
}

// Get the normal vector of the given cylinder in the world space
t_tuple	world_normal_cylinder(t_object *object, t_tuple point)
{
	t_cylinder	*cylinder;
	t_tuple		obj_p;
	t_tuple		obj_norm;
	t_tuple		world_norm_v;
	double		**inverse_m;

	cylinder = (t_cylinder *)(object->ptr);
	inverse_m = invert_matrix(object->transformation_matrix);
	obj_p = matrix_point_mul_4x4(inverse_m, point);
	if (fabs(obj_p.y - cylinder->max) < EPSILON)
		obj_norm = create_tuple(0, 1, 0, VECT);
	else if (fabs(obj_p.y - cylinder->min) < EPSILON)
		obj_norm = create_tuple(0, -1, 0, VECT);
	else
		obj_norm = create_tuple(obj_p.x, 0, obj_p.z, VECT);
	world_norm_v = get_world_norm(inverse_m, obj_norm);
	matrix_free(inverse_m, 4);
	return (world_norm_v);
}
