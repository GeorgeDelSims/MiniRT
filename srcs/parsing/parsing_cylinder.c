/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:07 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:04:08 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_insert_height_cylinder(t_cylinder *cylinder, char **tmp_ptr)
{
	int		param;
	char	*tmp;

	param = 0;
	tmp = *tmp_ptr;
	if (!is_valid_format(tmp, "DIA"))
		return (0);
	while (param < 1 && *tmp != '\0')
	{
		if (*tmp == ' ')
			break ;
		else
		{
			cylinder->height = ft_atof(tmp);
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

int	ft_insert_diameter_cylinder(t_cylinder *cylinder, char **tmp_ptr)
{
	int		param;
	char	*tmp;

	param = 0;
	tmp = *tmp_ptr;
	if (!is_valid_format(tmp, "DIA"))
		return (0);
	while (param < 1 && *tmp != '\0')
	{
		if (*tmp == ' ')
			break ;
		else
		{
			cylinder->diameter = ft_atof(tmp);
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

int	insert_cylinder_param(int param, t_cylinder *cylinder, char **tmp_ptr)
{
	if ((param == 0 && !ft_insert_centre(&cylinder->centre, tmp_ptr))
		|| (param == 1 && !ft_insert_vector(&cylinder->orientation, tmp_ptr))
		|| (param == 2 && !ft_insert_diameter_cylinder(cylinder, tmp_ptr))
		|| (param == 3 && !ft_insert_height_cylinder(cylinder, tmp_ptr))
		|| (param == 4 && !ft_insert_color(&cylinder->color, tmp_ptr)))
	{
		return (0);
	}
	return (1);
}

void	process_cylinder_params(t_cylinder *cylinder, char **tmp_ptr,
		t_scene *scene)
{
	int	param;

	param = 0;
	while (param < NB_ATR_CYLINDER && **tmp_ptr != '\0')
	{
		if (**tmp_ptr == ' ')
		{
			(*tmp_ptr)++;
			continue ;
		}
		validate_cylinder_new_element(*tmp_ptr, cylinder, scene);
		insert_cylinderparam_or_exit(param, cylinder, tmp_ptr, scene);
		param++;
	}
	check_cylinderparam_or_exit(param, cylinder, *tmp_ptr, scene);
}

void	create_cylinder(t_scene *scene, t_object *obj, char **tmp)
{
	char		*tmp_ptr;
	t_cylinder	*cylinder;

	tmp_ptr = *tmp;
	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	check_cylinder_allocation(cylinder, scene);
	process_cylinder_params(cylinder, &tmp_ptr, scene);
	cylinder->radius = cylinder->diameter / 2.0;
	cylinder->id = obj->id;
	cylinder->obj = obj;
	cylinder->closed = true;
	cylinder->min = cylinder->centre.y - cylinder->height / 2;
	cylinder->max = cylinder->centre.y + cylinder->height / 2;
	obj = &scene->objects[obj->id];
	obj->type = CYLINDER;
	obj->ptr = cylinder;
}
