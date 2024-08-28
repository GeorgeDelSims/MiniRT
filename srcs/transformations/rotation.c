/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:09:58 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:09:59 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// hardcodes a rotation matrix
// cos_a = cosinus angle etc.
static double	**get_rotation_matrix(double cos_a, double sin_a,
		double one_minus_cos, t_tuple axis)
{
	double	**rotation_matrix;

	rotation_matrix = matrix_alloc(4);
	rotation_matrix[0][0] = cos_a + axis.x * axis.x * one_minus_cos;
	rotation_matrix[0][1] = axis.x * axis.y * one_minus_cos - axis.z * sin_a;
	rotation_matrix[0][2] = axis.x * axis.z * one_minus_cos + axis.y * sin_a;
	rotation_matrix[0][3] = 0.0;
	rotation_matrix[1][0] = axis.y * axis.x * one_minus_cos + axis.z * sin_a;
	rotation_matrix[1][1] = cos_a + axis.y * axis.y * one_minus_cos;
	rotation_matrix[1][2] = axis.y * axis.z * one_minus_cos - axis.x * sin_a;
	rotation_matrix[1][3] = 0.0;
	rotation_matrix[2][0] = axis.z * axis.x * one_minus_cos - axis.y * sin_a;
	rotation_matrix[2][1] = axis.z * axis.y * one_minus_cos + axis.x * sin_a;
	rotation_matrix[2][2] = cos_a + axis.z * axis.z * one_minus_cos;
	rotation_matrix[2][3] = 0.0;
	rotation_matrix[3][0] = 0.0;
	rotation_matrix[3][1] = 0.0;
	rotation_matrix[3][2] = 0.0;
	rotation_matrix[3][3] = 1.0;
	return (rotation_matrix);
}

// Create a rotation matrix using Rodrigues' rotation formula
static double	**rodrigues_rotation_matrix(t_tuple axis, double angle)
{
	double	cos_a;
	double	sin_a;
	double	one_minus_cos;

	cos_a = cos(angle);
	sin_a = sin(angle);
	one_minus_cos = 1.0 - cos_a;
	axis = normalise(axis);
	return (get_rotation_matrix(cos_a, sin_a, one_minus_cos, axis));
}

// Build the rotation matrix to align a vector with another vector
double	**build_rotation_matrix(t_tuple current_dir, t_tuple target_dir)
{
	t_tuple	axis;
	double	angle;
	double	**rotation_matrix;

	current_dir = normalise(current_dir);
	target_dir = normalise(target_dir);
	axis = cross_prod(current_dir, target_dir);
	angle = acos(dot_prod(current_dir, target_dir));
	rotation_matrix = rodrigues_rotation_matrix(axis, angle);
	return (rotation_matrix);
}
