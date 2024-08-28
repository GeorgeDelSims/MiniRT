/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_arithmetic2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:12:12 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:12:13 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Scalar Division
t_tuple	div_tuple(t_tuple vector, double scalar)
{
	t_tuple	result;

	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	result.z = vector.z / scalar;
	result.type = vector.type;
	return (result);
}

// Square root of a double number
double	double_sqrt(double a)
{
	double	result;
	double	root;

	if (a <= 0)
		return (0);
	root = a;
	while (1)
	{
		result = (root + (a / root)) / 2;
		if (result == root || result == root + 1)
			break ;
		root = result;
	}
	return (result);
}

// Vector Magnitude  (= total length of a vector)
// magnitude = square root of (the sum of the vector elements squared)
// Pythagoras
// a vector with a magnitude of 1 is called a unit vector
double	magnitude(t_tuple vect)
{
	double	sum;

	sum = (vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z);
	return (double_sqrt(sum));
}

// Normalisation:
// The process of converting vectors into unit vectors (magnitude)
// keeps all calculations on a common scale
t_tuple	normalise(t_tuple vector)
{
	t_tuple	result;
	double	mag;

	mag = magnitude(vector);
	if (mag == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		result.type = vector.type;
	}
	else
	{
		result.x = vector.x / mag;
		result.y = vector.y / mag;
		result.z = vector.z / mag;
		result.type = vector.type;
	}
	return (result);
}

// Dot Product (or scalar product)
// multiplication of two vectors
double	dot_prod(t_tuple v1, t_tuple v2)
{
	double	dot;

	dot = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return (dot);
}
