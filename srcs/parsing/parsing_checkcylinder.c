/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkcylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:46 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:47 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_cylinderparam_or_exit(int actual, t_cylinder *cylinder,
		char *tmp_ptr, t_scene *scene)
{
	(void)cylinder;
	if (!check_valid_param(NB_ATR_CYLINDER, actual))
	{
		free_all_objects(scene);
		exit(1);
	}
	if (!is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees cylinder\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	insert_cylinderparam_or_exit(int param, t_cylinder *cylinder,
		char **tmp_ptr, t_scene *scene)
{
	if (!insert_cylinder_param(param, cylinder, tmp_ptr))
	{
		printf("Error\n Failed to insert cylinder parameters\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	validate_cylinder_new_element(char *tmp_ptr, t_cylinder *cylinder,
		t_scene *scene)
{
	(void)cylinder;
	if (is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees cylinder new element\n");
		free_all_objects(scene);
		exit(1);
	}
}

void	check_cylinder_allocation(t_cylinder *cylinder, t_scene *scene)
{
	if (!cylinder)
	{
		printf("Error\n Failed to create cylinder\n");
		free_all_objects(scene);
		exit(1);
	}
}
