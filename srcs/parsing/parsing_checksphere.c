/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checksphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:03 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:04:04 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_sphereparam_or_exit(int actual, t_sphere *sphere, char *tmp_ptr,
		t_scene *scene)
{
	(void)sphere;
	if (!check_valid_param(NB_ATR_SPHERE, actual))
	{
		free_all_objects(scene);
		exit(1);
	}
	if (!is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees sphere\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	insert_sphereparam_or_exit(int param, t_sphere *sphere, char **tmp_ptr,
		t_scene *scene)
{
	if (!insert_sphere_param(param, sphere, tmp_ptr))
	{
		printf("Error\n Failed to insert sphere parameters\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	validate_sphere_new_element(char *tmp_ptr, t_sphere *sphere,
		t_scene *scene)
{
	(void)sphere;
	if (is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees sphere new element\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	check_sphere_allocation(t_sphere *sphere, t_scene *scene)
{
	if (!sphere)
	{
		printf("Error\n Failed to create sphere\n");
		free_all_objects(scene);
		exit(1);
	}
}
