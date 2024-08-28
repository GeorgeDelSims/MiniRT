/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:21 by gsims             #+#    #+#             */
/*   Updated: 2024/08/24 10:56:46 by rtauzin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	initialize_scene_objects(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->object_count)
	{
		scene->objects[i].ptr = NULL;
		scene->objects[i].transformation_matrix = NULL;
		scene->camera.trans = NULL;
		i++;
	}
}

int	count_objects(char *rt_file)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = rt_file;
	while (*tmp)
	{
		if (ft_strncmp(tmp, "sp", 2) == 0)
			count++;
		else if (ft_strncmp(tmp, "pl", 2) == 0)
			count++;
		else if (ft_strncmp(tmp, "cy", 2) == 0)
			count++;
		tmp++;
	}
	return (count);
}

void	parse_object(t_scene *scene, char **tmp, int *index_obj)
{
	if (ft_strncmp(*tmp, "sp", 2) == 0)
	{
		*tmp += 2;
		ft_init_obj(scene, tmp, SPHERE, (*index_obj)++);
	}
	else if (ft_strncmp(*tmp, "cy", 2) == 0)
	{
		*tmp += 2;
		ft_init_obj(scene, tmp, CYLINDER, (*index_obj)++);
	}
	else if (ft_strncmp(*tmp, "pl", 2) == 0)
	{
		*tmp += 2;
		ft_init_obj(scene, tmp, PLANE, (*index_obj)++);
	}
}

void	parse_scene_element(t_scene *scene, char **tmp)
{
	if (ft_strncmp(*tmp, "L", 1) == 0)
	{
		*tmp += 1;
		ft_insert_light(scene, tmp);
	}
	else if (ft_strncmp(*tmp, "C", 1) == 0)
	{
		*tmp += 1;
		ft_insert_camera(scene, tmp);
	}
	else if (ft_strncmp(*tmp, "A", 1) == 0)
	{
		*tmp += 1;
		ft_insert_ambient(scene, tmp);
	}
}

t_scene	ft_parsing_rt(t_scene *scene)
{
	char	*tmp;
	int		index_obj;

	index_obj = 0;
	tmp = scene->rt_file;
	scene->object_count = count_objects(scene->rt_file);
	scene->objects = (t_object *)malloc(sizeof(t_object) * scene->object_count);
	check_allocation(scene);
	initialize_scene_objects(scene);
	check_misconfiguration_rt_file(scene);
	check_first_element(&tmp, scene);
	while (*tmp)
	{
		parse_object(scene, &tmp, &index_obj);
		parse_scene_element(scene, &tmp);
		tmp++;
	}
	free(scene->rt_file);
	return (*scene);
}
