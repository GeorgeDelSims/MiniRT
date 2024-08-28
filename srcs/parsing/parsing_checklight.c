/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checklight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:58 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:59 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_lightparam_or_exit(int actual, t_light *light, char *tmp_ptr,
		t_scene *scene)
{
	if (!check_valid_param(NB_ATR_LIGHT, actual))
	{
		free(light);
		free_all_objects(scene);
		exit(1);
	}
	if (!is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees light\n");
		free(light);
		free_all_objects(scene);
		exit(1);
	}
}

void	insert_lightparam_or_exit(int param, t_light *light, char **tmp_ptr,
		t_scene *scene)
{
	if (!insert_light_param(param, light, tmp_ptr))
	{
		printf("Error\n Failed to insert light parameters\n");
		free(light);
		free_all_objects(scene);
		exit(1);
	}
}

void	validate_light_new_element(char *tmp_ptr, t_light *light,
		t_scene *scene)
{
	if (is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees light new element\n");
		free(light);
		free_all_objects(scene);
		exit(1);
	}
}

void	check_light_allocation(t_light *light, t_scene *scene)
{
	if (!light)
	{
		printf("Error\n Failed to create light\n");
		free_all_objects(scene);
		exit(1);
	}
}
