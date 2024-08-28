/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:41 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:04:42 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_matrix(double **matrix, size_t size)
{
	size_t	row;

	row = 0;
	if (matrix)
	{
		while (row < size)
		{
			free(matrix[row]);
			row++;
		}
		free(matrix);
	}
}

void	free_camera(t_camera *camera)
{
	if (camera->trans)
	{
		free_matrix(camera->trans, 4);
		camera->trans = NULL;
	}
}

void	free_object(t_object *obj)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (obj->type == SPHERE)
	{
		sphere = (t_sphere *)obj->ptr;
		free(sphere);
	}
	else if (obj->type == PLANE)
	{
		plane = (t_plane *)obj->ptr;
		free(plane);
	}
	else if (obj->type == CYLINDER)
	{
		cylinder = (t_cylinder *)obj->ptr;
		free(cylinder);
	}
}

void	free_transformation_matrix(double **matrix)
{
	size_t	row;

	row = 0;
	if (matrix)
	{
		while (row < 4)
		{
			free(matrix[row]);
			row++;
		}
		free(matrix);
	}
}

void	free_all_objects(t_scene *scene)
{
	int			i;
	t_object	*obj;

	i = 0;
	while (i < scene->object_count)
	{
		obj = &scene->objects[i];
		if (obj->ptr != NULL)
		{
			free_transformation_matrix(obj->transformation_matrix);
			free_object(obj);
			obj->ptr = NULL;
		}
		i++;
	}
	free(scene->objects);
	scene->objects = NULL;
	scene->object_count = 0;
	free_camera(&scene->camera);
}
