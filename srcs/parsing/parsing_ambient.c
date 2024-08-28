/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:25 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:26 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_insert_ambient_light(t_ambient *ambient, char **tmp_ptr)
{
	int		param;
	char	*tmp;

	param = 0;
	tmp = *tmp_ptr;
	if (!is_valid_format(tmp, "AMB"))
		return (0);
	while (param < 1 && *tmp != '\0')
	{
		if (*tmp == ' ')
			break ;
		else
		{
			ambient->ambient_light = ft_atof(tmp);
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

int	insert_ambient_param(int param, t_ambient *ambient, char **tmp_ptr)
{
	if (param == 0)
	{
		if (!ft_insert_ambient_light(ambient, tmp_ptr))
			return (0);
	}
	else if (param == 1)
	{
		if (!ft_insert_color(&ambient->color, tmp_ptr))
			return (0);
	}
	return (1);
}

t_scene	ft_insert_ambient(t_scene *scene, char **tmp)
{
	int			param;
	char		*tmp_ptr;
	t_ambient	*ambient;

	param = 0;
	tmp_ptr = *tmp;
	ambient = (t_ambient *)malloc(sizeof(t_ambient));
	check_ambient_allocation(ambient, scene);
	while (param < NB_ATR_AMBIENT && *tmp_ptr != '\0')
	{
		if (*tmp_ptr == ' ')
		{
			tmp_ptr++;
			continue ;
		}
		validate_ambiant_new_element(tmp_ptr, ambient, scene);
		insert_ambiantparam_or_exit(param, ambient, &tmp_ptr, scene);
		param++;
	}
	check_ambiantparam_or_exit(param, ambient, tmp_ptr, scene);
	scene->ambient = *ambient;
	free(ambient);
	return (*scene);
}
