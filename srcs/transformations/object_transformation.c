/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:09:50 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:10:48 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// build sphere transformation matrix
static double	**build_trans_matrix_sphere(t_sphere *sphere)
{
	double	**transl_matrix;
	double	**scal_matrix;
	double	**transf_matrix;

	scal_matrix = scaling_matrix(sphere->radius, sphere->radius,
			sphere->radius);
	transl_matrix = translation_matrix(sphere->centre.x, sphere->centre.y,
			sphere->centre.z);
	transf_matrix = matrix_mul(transl_matrix, scal_matrix);
	matrix_free(scal_matrix, 4);
	matrix_free(transl_matrix, 4);
	return (transf_matrix);
}

// apply a sphere's transformation matrix to itself (centre and radius etc)
void	apply_trans_matrix_sphere(t_sphere *sphere)
{
	double	avg_scaling_factor;

	sphere->obj->transformation_matrix = build_trans_matrix_sphere(sphere);
	sphere->centre = matrix_point_mul(sphere->obj->transformation_matrix,
			create_tuple(0, 0, 0, POINT));
	avg_scaling_factor = (sphere->obj->transformation_matrix[0][0]
			+ sphere->obj->transformation_matrix[1][1]
			+ sphere->obj->transformation_matrix[2][2]) / 3;
	sphere->radius = 1 * avg_scaling_factor;
}

// Apply transformation matrix to plane properties
void	apply_trans_matrix_plane(t_plane *plane)
{
	plane->point = matrix_point_mul(plane->obj->transformation_matrix,
			plane->point);
	plane->normal = matrix_vect_mul(plane->obj->transformation_matrix,
			plane->normal);
	plane->normal = normalise(plane->normal);
}

// build transformation matrix for a cylinder
static double	**build_trans_matrix_cyl(t_cylinder *cylinder)
{
	double	**rot_matrix;
	double	**transl_matrix;
	double	**transf_matrix;
	double	**scale_matrix;
	double	**temp_matrix;

	rot_matrix = build_rotation_matrix(create_tuple(0, 1, 0, VECT),
			cylinder->orientation);
	scale_matrix = scaling_matrix(cylinder->radius, cylinder->height,
			cylinder->radius);
	transl_matrix = translation_matrix(cylinder->centre.x, cylinder->centre.y,
			cylinder->centre.z);
	temp_matrix = matrix_mul(rot_matrix, scale_matrix);
	transf_matrix = matrix_mul(transl_matrix, temp_matrix);
	matrix_free(rot_matrix, 4);
	matrix_free(scale_matrix, 4);
	matrix_free(transl_matrix, 4);
	matrix_free(temp_matrix, 4);
	return (transf_matrix);
}

// Build and apply transformation matrix to cylinder properties
void	apply_trans_matrix_cyl(t_cylinder *cyl)
{
	double	scaling_factor_radius;

	cyl->obj->transformation_matrix = build_trans_matrix_cyl(cyl);
	cyl->centre = matrix_point_mul(cyl->obj->transformation_matrix,
			create_tuple(0, 0, 0, POINT));
	scaling_factor_radius = fabs((cyl->obj->transformation_matrix[0][0]
				+ cyl->obj->transformation_matrix[2][2]) / 2);
	cyl->radius = scaling_factor_radius;
	cyl->diameter = cyl->radius * 2;
	cyl->min = 0;
	cyl->max = cyl->min + cyl->height;
	cyl->orientation = matrix_vect_mul(cyl->obj->transformation_matrix,
			create_tuple(0, 1, 0, VECT));
	cyl->orientation = normalise(cyl->orientation);
}
