/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:03 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:04:19 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	insert_plane_param(int param, t_plane *plane, char **tmp_ptr)
{
	if (param == 0)
		ft_insert_centre(&plane->point, tmp_ptr);
	else if (param == 1)
		ft_insert_vector(&plane->normal, tmp_ptr);
	else if (param == 2)
		ft_insert_color(&plane->color, tmp_ptr);
	param++;
	return (1);
}

void	create_plane(t_scene *scene, t_object *obj, char **tmp, int index)
{
	int		param;
	char	*tmp_ptr;
	t_plane	*plane;

	param = 0;
	tmp_ptr = *tmp;
	plane = (t_plane *)malloc(sizeof(t_plane));
	check_plane_allocation(plane, scene);
	while (param < NB_ATR_PLANE && *tmp_ptr != '\0')
	{
		if (*tmp_ptr == ' ')
		{
			tmp_ptr++;
			continue ;
		}
		validate_plane_new_element(tmp_ptr, plane, scene);
		insert_planeparam_or_exit(param, plane, &tmp_ptr, scene);
		param++;
	}
	check_planeparam_or_exit(param, plane, tmp_ptr, scene);
	plane->obj = &scene->objects[index];
	plane->obj = obj;
	plane->id = obj->id;
	obj = &scene->objects[scene->object_count];
	scene->objects[index].ptr = plane;
}
