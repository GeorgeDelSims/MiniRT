/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkplane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:01 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:04:02 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_planeparam_or_exit(int actual, t_plane *plane, char *tmp_ptr,
		t_scene *scene)
{
	(void)plane;
	if (!check_valid_param(NB_ATR_PLANE, actual))
	{
		free_all_objects(scene);
		exit(1);
	}
	if (!is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees plane\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	insert_planeparam_or_exit(int param, t_plane *plane, char **tmp_ptr,
		t_scene *scene)
{
	if (!insert_plane_param(param, plane, tmp_ptr))
	{
		printf("Error\n Failed to insert plane parameters\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	validate_plane_new_element(char *tmp_ptr, t_plane *plane,
		t_scene *scene)
{
	(void)plane;
	if (is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees plane new element\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	check_plane_allocation(t_plane *plane, t_scene *scene)
{
	if (!plane)
	{
		printf("Error\n Failed to create plane\n");
		free_all_objects(scene);
		exit(1);
	}
}
