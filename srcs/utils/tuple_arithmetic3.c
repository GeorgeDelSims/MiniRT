/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_arithmetic3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:12:15 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:12:16 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Cross product of two vectors
// Returns the vector perpendicular to both original vectors in 3D
t_tuple	cross_prod(t_tuple v1, t_tuple v2)
{
	t_tuple	result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	result.type = 0;
	return (result);
}

// print the contents of a tuple for testing purposes
void	print_tuple(t_tuple tup)
{
	printf("x : %f\n", tup.x);
	printf("y : %f\n", tup.y);
	printf("z : %f\n", tup.z);
	printf("type : %f\n", tup.type);
}
