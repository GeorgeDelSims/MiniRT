/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_arithmetic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:12:09 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:12:10 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* ---------- VECTOR ARITHMETIC ---------- */

// creates a tuple from three double values
// The type defines whether its a point or a vector
t_tuple	create_tuple(double x, double y, double z, double type)
{
	t_tuple	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.type = type;
	return (vector);
}

// Tuple addition functions
// works for adding a point to a vector or a vector to a vector
t_tuple	add_tuple(t_tuple v1, t_tuple v2)
{
	t_tuple	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.type = v1.type + v2.type;
	return (result);
}

// subtract a vector or point from another one, or a vector from a point
// you can't subtract a point from a vector
t_tuple	subtr_tuple(t_tuple v1, t_tuple v2)
{
	t_tuple	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.type = v1.type - v2.type;
	return (result);
}

// Get the opposite of a vector
t_tuple	negate_tuple(t_tuple vector)
{
	return (create_tuple(-vector.x, -vector.y, -vector.z, vector.type));
}

// Scalar mutiplication
t_tuple	scale_tuple(t_tuple vector, double scalar)
{
	t_tuple	result;

	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;
	result.type = vector.type;
	return (result);
}
