/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:10:01 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:11:34 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Creates a translation matrix
double	**translation_matrix(double x, double y, double z)
{
	double	**trans_matrix;

	trans_matrix = identity_matrix(4);
	trans_matrix[0][3] += x;
	trans_matrix[1][3] += y;
	trans_matrix[2][3] += z;
	return (trans_matrix);
}

// Creates a scaling matrix (which moves a point by multiplication)
// when applied to an object at the origin, it scales all points of the object
// REflection is scaling by a negative value
double	**scaling_matrix(double x, double y, double z)
{
	double	**scaling;

	scaling = identity_matrix(4);
	scaling[0][0] *= x;
	scaling[1][1] *= y;
	scaling[2][2] *= z;
	return (scaling);
}

double	**create_translation_matrix(t_object *obj)
{
	return (translation_matrix(((t_sphere *)obj->ptr)->centre.x,
			((t_sphere *)obj->ptr)->centre.y,
			((t_sphere *)obj->ptr)->centre.z));
}

double	**create_scaling_matrix_sphere(t_object *obj)
{
	return (scaling_matrix(((t_sphere *)obj->ptr)->radius,
			((t_sphere *)obj->ptr)->radius, ((t_sphere *)obj->ptr)->radius));
}

double	**init_matrix_scalandtransl(t_object *obj)
{
	double	**transf_matrix;
	double	**scal_matrix;
	double	**mul_matrix;

	if (obj->type == SPHERE)
	{
		transf_matrix = create_translation_matrix(obj);
		scal_matrix = create_scaling_matrix_sphere(obj);
		mul_matrix = matrix_mul(scal_matrix, transf_matrix);
		return (mul_matrix);
	}
	return (NULL);
}
