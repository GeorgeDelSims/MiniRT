/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tuple_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:58 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:11:59 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// custom Matrix * point multiplication function
t_tuple	matrix_point_mul_4x4(double **m, t_tuple p)
{
	t_tuple	res;

	res.x = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3];
	res.y = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3];
	res.z = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3];
	res.type = POINT;
	return (res);
}

// custom Matrix * vector multiplication function
t_tuple	matrix_vect_mul_3x3(double **m, t_tuple v)
{
	t_tuple	res;

	res.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
	res.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
	res.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
	res.type = VECT;
	return (res);
}

// custom Matrix 3x3 transpose function
double	**trans_3x3(double **matrix)
{
	double	**transposed;

	transposed = matrix_alloc(3);
	transposed[0][0] = matrix[0][0];
	transposed[0][1] = matrix[1][0];
	transposed[0][2] = matrix[2][0];
	transposed[1][0] = matrix[0][1];
	transposed[1][1] = matrix[1][1];
	transposed[1][2] = matrix[2][1];
	transposed[2][0] = matrix[0][2];
	transposed[2][1] = matrix[1][2];
	transposed[2][2] = matrix[2][2];
	return (transposed);
}

// Multiply a tuple by a matrix
t_tuple	matrix_point_mul(double **m, t_tuple p)
{
	t_tuple	res;

	res.x = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3];
	res.y = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3];
	res.z = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3];
	res.type = POINT;
	return (res);
}

// Multiply a tuple by a matrix
t_tuple	matrix_vect_mul(double **m, t_tuple v)
{
	t_tuple	res;

	res.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
	res.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
	res.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
	res.type = VECT;
	return (res);
}
