/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:29 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:30 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_insert_fov(t_camera *camera, char **tmp_ptr)
{
	int		param;
	char	*tmp;

	param = 0;
	tmp = *tmp_ptr;
	if (!is_valid_format(tmp, "FOV"))
		return (0);
	while (param < 1 && *tmp != '\0')
	{
		if (*tmp == ' ')
			break ;
		else
		{
			camera->fov = ft_atof(tmp);
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

int	ft_insert_vector(t_tuple *vect, char **tmp_ptr)
{
	if (!is_valid_format(*tmp_ptr, "VEC"))
		return (0);
	return (parse_centre_params(vect, tmp_ptr));
}

int	insert_camera_param(int param, t_camera *camera, char **tmp_ptr)
{
	if (param == 0)
	{
		if (!ft_insert_centre(&camera->origin, tmp_ptr))
			return (0);
	}
	else if (param == 1)
	{
		if (!ft_insert_vector(&camera->orientation, tmp_ptr))
			return (0);
	}
	else if (param == 2)
	{
		if (!ft_insert_fov(camera, tmp_ptr))
			return (0);
	}
	return (1);
}

t_scene	ft_insert_camera(t_scene *scene, char **tmp)
{
	int			param;
	char		*tmp_ptr;
	t_camera	*camera;

	param = 0;
	tmp_ptr = *tmp;
	camera = (t_camera *)malloc(sizeof(t_camera));
	check_camera_allocation(camera, scene);
	while (param < NB_ATR_CAMERA && *tmp_ptr != '\0')
	{
		if (*tmp_ptr == ' ')
		{
			tmp_ptr++;
			continue ;
		}
		validate_camera_new_element(tmp_ptr, camera, scene);
		insert_cameraparam_or_exit(param, camera, &tmp_ptr, scene);
		param++;
	}
	check_cameraparam_or_exit(param, camera, tmp_ptr, scene);
	scene->camera = *camera;
	scene->camera = compute_camera_values(scene->camera, WIDTH, HEIGHT,
			camera->fov);
	free(camera);
	return (*scene);
}
