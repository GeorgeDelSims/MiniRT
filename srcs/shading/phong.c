/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:06:06 by gsims             #+#    #+#             */
/*   Updated: 2024/08/24 14:54:09 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Combine surface color of object with light intensity
// provides the color under the circumstances of the light sources available
static t_color	get_effective_color(t_object obj, t_scene *s)
{
	t_color	effective_color;
	double	factor;

	factor = s->ambient.ambient_light;
	effective_color.red = obj.color.red * s->light_source.intensity.red * (1
			- factor) + s->ambient.color.red * factor;
	effective_color.green = obj.color.green * s->light_source.intensity.green
		* (1 - factor) + s->ambient.color.green * factor;
	effective_color.blue = obj.color.blue * s->light_source.intensity.blue * (1
			- factor) + s->ambient.color.blue * factor;
	return (effective_color);
}

// for the shaded parts of objects,
static t_phong	compute_unlit_surface(t_phong p, double light_dot_normal)
{
	p.ambient = add_scalar_to_color(p.ambient, light_dot_normal);
	p.diffuse = (t_color){0, 0, 0};
	p.specular = (t_color){0, 0, 0};
	return (p);
}

// helper function to compute the specular (white dot) light on objects
// reflect_dot_eye = cosine of angle between reflection vect and eye vect
// if it is negative the light reflects away from the eye
static t_color	get_spec(t_object *object, t_light light, t_phong p,
		t_tuple eye_vect)
{
	t_color	result;
	double	factor;
	double	reflect_dot_eye;
	t_tuple	reflect_vect;

	reflect_vect = reflect(negate_tuple(p.light_vect), p.normal_vect);
	reflect_vect = normalise(reflect_vect);
	reflect_dot_eye = dot_prod(reflect_vect, eye_vect);
	if (reflect_dot_eye <= 0)
		return ((t_color){0, 0, 0});
	else
	{
		factor = pow(reflect_dot_eye, object->material.shininess);
		result = combine_color_two(light.intensity, object->material.specular,
				factor);
		return (result);
	}
}

// Get phong struct for lighting calculations
// first gets effective colour, adds general ambient lighting
// gets normal vectors for different shapes
static t_phong	get_phong_values(t_ray *ray, t_scene *scene)
{
	t_phong	p;

	p.effective_color = get_effective_color(*(ray->object), scene);
	p.light_vect = normalise(subtr_tuple(scene->light_source.position,
				ray->point));
	p.ambient = combine_color(p.effective_color, ray->object->material.ambient);
	p.ambient = add_scalar_to_color(p.ambient, scene->ambient.ambient_light);
	if (ray->object->type == PLANE)
		p.normal_vect = ((t_plane *)(ray->object->ptr))->normal;
	else if (ray->object->type == CYLINDER)
		p.normal_vect = world_normal_cylinder(ray->object, ray->point);
	else
		p.normal_vect = world_normal_sphere(ray->object, ray->point);
	p.normal_vect = normalise(p.normal_vect);
	return (p);
}

// Phong lighting algorithm to combine ambient, diffuse and specular light
// based on light, material properties and eye vector
// if dot product == 0 -> interior of object
t_color	phong_lighting(t_ray *ray, t_scene *scene, t_tuple eye_vect, double dot)
{
	t_phong	p;
	t_color	color;
	double	light_dot_normal;
	bool	shad;

	if (dot <= 0)
		return ((t_color){0, 0, 0});
	p = get_phong_values(ray, scene);
	light_dot_normal = dot_prod(p.light_vect, p.normal_vect);
	if (light_dot_normal <= 0)
		p = compute_unlit_surface(p, light_dot_normal);
	else
	{
		p.diffuse = combine_color_two(p.effective_color,
				ray->object->material.diffuse, light_dot_normal);
		p.specular = get_spec(ray->object, scene->light_source, p, eye_vect);
	}
	shad = false;
	if (is_shadow(scene, ray->point) == true)
		shad = true;
	color = combine_shading(p.ambient, p.diffuse, p.specular, shad);
	return (color);
}
