/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:09:53 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:09:54 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// initiates values for sphere at obj struct level
static void	init_sphere_obj(t_scene *s, t_object *obj, char **tmp, int i)
{
	s->objects[i].id = i;
	s->objects[i].intersect_func = intersect_sphere;
	ft_create_sphere(s, obj, tmp);
	set_default_material(&s->objects[i]);
	s->objects[i].color = ((t_sphere *)s->objects[i].ptr)->color;
	apply_trans_matrix_sphere((t_sphere *)obj->ptr);
}

// initiates values for plane at obj struct level
static void	init_plane_obj(t_scene *s, t_object *obj, char **tmp, int i)
{
	s->objects[i].id = i;
	s->objects[i].intersect_func = intersect_plane;
	create_plane(s, obj, tmp, i);
	set_default_material(&s->objects[i]);
	s->objects[i].color = ((t_plane *)s->objects[i].ptr)->color;
	obj->transformation_matrix = identity_matrix(4);
	apply_trans_matrix_plane((t_plane *)obj->ptr);
}

// initiates values for cylinder at obj struct level
static void	init_cylinder_obj(t_scene *s, t_object *obj, char **tmp, int i)
{
	s->objects[i].id = i;
	s->objects[i].intersect_func = intersect_cylinder;
	create_cylinder(s, obj, tmp);
	set_default_material(&s->objects[i]);
	s->objects[i].color = ((t_cylinder *)s->objects[i].ptr)->color;
	apply_trans_matrix_cyl((t_cylinder *)obj->ptr);
}

// fonction qui initialise les differents types d'objet
void	ft_init_obj(t_scene *s, char **data, int type, int i)
{
	t_object	*obj;

	obj = &s->objects[i];
	obj->type = type;
	obj->id = i;
	if (type == SPHERE)
		init_sphere_obj(s, obj, data, i);
	else if (type == CYLINDER)
		init_cylinder_obj(s, obj, data, i);
	else if (type == PLANE)
		init_plane_obj(s, obj, data, i);
	else
		perror("nonexistant type\n");
}
