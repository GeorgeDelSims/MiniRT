/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:14:01 by gsims             #+#    #+#             */
/*   Updated: 2024/08/26 17:45:51 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Function to convert degrees to radians
double	deg_to_rad(double degrees)
{
	return (degrees * M_PI / 180.0);
}

// compute the size in world space units of pixels on the canvas
t_camera	compute_camera_values(t_camera camera, double hsize, double vsize,
		double fov)
{
	double	half_view;
	double	aspect_ratio;

	camera.hsize = hsize;
	camera.vsize = vsize;
	camera.fov = deg_to_rad(fov);
	half_view = fabs(tan(camera.fov / 2));
	aspect_ratio = hsize / vsize;
	if (aspect_ratio >= 1)
	{
		camera.half_width = half_view;
		camera.half_height = half_view / aspect_ratio;
	}
	else
	{
		camera.half_width = half_view * aspect_ratio;
		camera.half_height = half_view;
	}
	camera.pixel_size = (camera.half_width * 2) / hsize;
	camera.origin.type = POINT;
	camera.orientation.type = VECT;
	camera.trans = view_transform(camera.origin, add_tuple(camera.origin,
				camera.orientation));
	return (camera);
}

// creates the view matrix
static double	**create_view_matrix(t_tuple from, t_tuple f_v, t_tuple l_v,
		t_tuple up_v)
{
	double	**orientation;
	double	**translation;
	double	**view_matrix;

	orientation = identity_matrix(4);
	orientation[0][0] = l_v.x;
	orientation[0][1] = l_v.y;
	orientation[0][2] = l_v.z;
	orientation[1][0] = up_v.x;
	orientation[1][1] = up_v.y;
	orientation[1][2] = up_v.z;
	orientation[2][0] = -f_v.x;
	orientation[2][1] = -f_v.y;
	orientation[2][2] = -f_v.z;
	translation = translation_matrix(from.x, from.y, from.z);
	view_matrix = matrix_mul(translation, orientation);
	matrix_free(orientation, 4);
	matrix_free(translation, 4);
	return (view_matrix);
}

// get up vector according to forward vect
// Try with the first reference up vector (0, 1, 0)
// If the result is near zero (parallel vectors),
// try the second reference up vector (0, 0, 1)
static t_tuple	calculate_up_vect(t_tuple forward_vect)
{
	t_tuple	left_vect;
	t_tuple	up_reference;
	t_tuple	up_vect;

	up_reference = create_tuple(0, 1, 0, VECT);
	left_vect = cross_prod(forward_vect, up_reference);
	if (magnitude(left_vect) < EPSILON)
	{
		up_reference = create_tuple(0, 0, 1, VECT);
		left_vect = cross_prod(forward_vect, up_reference);
	}
	up_vect = cross_prod(left_vect, forward_vect);
	return (normalise(up_vect));
}

// creates a transformation matrix that orients the view
// according to the the from point (origin),
// the to point (origin + directional vector), and the up vector
double	**view_transform(t_tuple from, t_tuple to)
{
	t_tuple	f_v;
	t_tuple	l_v;
	t_tuple	up_v;
	t_tuple	up;

	f_v = normalise(subtr_tuple(to, from));
	up = calculate_up_vect(f_v);
	l_v = normalise(cross_prod(f_v, up));
	up_v = normalise(cross_prod(l_v, f_v));
	return (create_view_matrix(from, f_v, l_v, up_v));
}
