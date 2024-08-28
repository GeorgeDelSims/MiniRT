/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkambient.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:39 by gsims             #+#    #+#             */
/*   Updated: 2024/08/24 13:10:43 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_ambiantparam_or_exit(int actual, t_ambient *ambient,
		char *tmp_ptr, t_scene *scene)
{
	if (!check_valid_param(NB_ATR_AMBIENT, actual))
	{
		free(ambient);
		free_all_objects(scene);
		exit(1);
	}
	if (!is_new_element(tmp_ptr))
	{
		printf("Error\nInvalid format des donnees ambiant\n");
		free(ambient);
		free_all_objects(scene);
		exit(1);
	}
}

void	insert_ambiantparam_or_exit(int param, t_ambient *ambient,
		char **tmp_ptr, t_scene *scene)
{
	if (!insert_ambient_param(param, ambient, tmp_ptr))
	{
		printf("Error\nFailed to insert ambient light parameters\n");
		free(ambient);
		free_all_objects(scene);
		exit(1);
	}
}

void	validate_ambiant_new_element(char *tmp_ptr, t_ambient *ambient,
		t_scene *scene)
{
	if (is_new_element(tmp_ptr))
	{
		printf("Error\nInvalid format des donnees ambiant new element\n");
		free(ambient);
		free_all_objects(scene);
		exit(1);
	}
}

void	check_ambient_allocation(t_ambient *ambient, t_scene *scene)
{
	if (!ambient)
	{
		printf("Error\nFailed to create ambient light\n");
		free_all_objects(scene);
		exit(1);
	}
}
