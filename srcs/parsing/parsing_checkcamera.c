/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkcamera.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:42 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:43 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_cameraparam_or_exit(int actual, t_camera *camera, char *tmp_ptr,
		t_scene *scene)
{
	if (!check_valid_param(NB_ATR_CAMERA, actual))
	{
		free(camera);
		free_all_objects(scene);
		exit(1);
	}
	if (!is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees camera\n");
		free(camera);
		free_all_objects(scene);
		exit(1);
	}
}

void	insert_cameraparam_or_exit(int param, t_camera *camera, char **tmp_ptr,
		t_scene *scene)
{
	if (!insert_camera_param(param, camera, tmp_ptr))
	{
		printf("Error\n Failed to insert camera parameters\n");
		free(camera);
		free_all_objects(scene);
		exit(1);
	}
}

void	validate_camera_new_element(char *tmp_ptr, t_camera *camera,
		t_scene *scene)
{
	if (is_new_element(tmp_ptr))
	{
		printf("Error\n Invalid format des donnees camera new element\n");
		free(camera);
		free_all_objects(scene);
		exit(1);
	}
}

void	check_camera_allocation(t_camera *camera, t_scene *scene)
{
	if (!camera)
	{
		printf("Error\n Failed to create camera\n");
		free_all_objects(scene);
		exit(1);
	}
}
