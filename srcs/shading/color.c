/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:05:39 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:08:01 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Creates color struct
t_color	create_color(double r, double g, double b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

// Makes sure values don't go higher than 1 or lower than -1
static void	normalise_color(t_color *color)
{
	if (color->red > 1)
		color->red = 1.0;
	if (color->green > 1)
		color->green = 1.0;
	if (color->blue > 1)
		color->blue = 1.0;
	if (color->red < -1)
		color->red = -1.0;
	if (color->green < -1)
		color->green = -1.0;
	if (color->blue < -1)
		color->blue = -1.0;
}

// Color scalar addition
t_color	add_scalar_to_color(t_color color, double scalar)
{
	t_color	result;

	result.red = color.red + scalar;
	result.green = color.green + scalar;
	result.blue = color.blue + scalar;
	normalise_color(&result);
	return (result);
}

// Color scalar multiplication
t_color	mul_scalar_with_color(t_color color, double scalar)
{
	t_color	result;

	result.red = color.red * scalar;
	result.green = color.green * scalar;
	result.blue = color.blue * scalar;
	normalise_color(&result);
	return (result);
}

// Comnbine amb / dif and spec lighting into one color struct
t_color	combine_shading(t_color amb, t_color dif, t_color spec, bool shad)
{
	t_color	result;
	double	a_fact;
	double	d_fact;
	double	s_fact;

	if (shad == false)
	{
		a_fact = 0.3;
		d_fact = 0.6;
		s_fact = 0.4;
	}
	else
	{
		a_fact = 0.3;
		d_fact = 0;
		s_fact = 0;
	}
	result.red = (amb.red * a_fact + dif.red * d_fact + spec.red * s_fact);
	result.green = (amb.green * a_fact + dif.green * d_fact + spec.green
			* s_fact);
	result.blue = (amb.blue * a_fact + dif.blue * d_fact + spec.blue * s_fact);
	normalise_color(&result);
	return (result);
}
