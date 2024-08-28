/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:12 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:05:08 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_insert_brightness(t_light *light, char **tmp_ptr)
{
	int		param;
	char	*tmp;

	param = 0;
	tmp = *tmp_ptr;
	if (!is_valid_format(tmp, "BRI"))
		return (0);
	while (param < 1 && *tmp != '\0')
	{
		if (*tmp == ' ')
			break ;
		else
		{
			light->brightness = ft_atof(tmp);
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

int	insert_light_param(int param, t_light *light, char **tmp_ptr)
{
	if (param == 0)
	{
		if (!ft_insert_centre(&light->position, tmp_ptr))
			return (0);
	}
	else if (param == 1)
	{
		ft_insert_brightness(light, tmp_ptr);
	}
	else if (param == 2)
	{
		if (!ft_insert_color(&light->intensity, tmp_ptr))
			return (0);
	}
	return (1);
}

t_scene	ft_insert_light(t_scene *scene, char **tmp)
{
	int		param;
	char	*tmp_ptr;
	t_light	*light;

	param = 0;
	tmp_ptr = *tmp;
	light = (t_light *)malloc(sizeof(t_light));
	check_light_allocation(light, scene);
	while (param < NB_ATR_LIGHT && *tmp_ptr != '\0')
	{
		if (*tmp_ptr == ' ')
		{
			tmp_ptr++;
			continue ;
		}
		validate_light_new_element(tmp_ptr, light, scene);
		insert_lightparam_or_exit(param, light, &tmp_ptr, scene);
		param++;
	}
	check_lightparam_or_exit(param, light, tmp_ptr, scene);
	scene->light_source = *light;
	free(light);
	return (*scene);
}
