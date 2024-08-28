/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:06:00 by gsims             #+#    #+#             */
/*   Updated: 2024/08/24 13:05:38 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// sets a default material for given object
// replaces and frees the previous material struct if it exists
void	set_default_material(t_object *object)
{
	object->material.ambient = 0.2;
	object->material.diffuse = 0.8;
	object->material.specular = 0.9;
	object->material.shininess = 200.0;
}

// Function to multiply intensity by material characteristics
t_color	combine_color(t_color intensity, double scalar)
{
	t_color	result;

	result.red = intensity.red * scalar;
	result.green = intensity.green * scalar;
	result.blue = intensity.blue * scalar;
	return (result);
}

// multiply intensity by two factors
t_color	combine_color_two(t_color intensity, double scalar1, double scalar2)
{
	t_color	result;

	result.red = intensity.red * scalar1 * scalar2;
	result.green = intensity.green * scalar1 * scalar2;
	result.blue = intensity.blue * scalar1 * scalar2;
	return (result);
}

// combines material properties to a new color
t_color	apply_mat_properties(t_color intensity, t_object *object)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	result;

	ambient = combine_color(intensity, object->material.ambient);
	diffuse = combine_color(intensity, object->material.diffuse);
	specular = combine_color(intensity, object->material.specular);
	result.red = ambient.red + diffuse.red + specular.red;
	result.green = ambient.green + diffuse.green + specular.green;
	result.blue = ambient.blue + diffuse.blue + specular.blue;
	return (result);
}
