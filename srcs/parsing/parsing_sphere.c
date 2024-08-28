/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:37 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:04:38 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_insert_centre(t_tuple *vect, char **tmp_ptr)
{
	if (!is_valid_format(*tmp_ptr, "CEN"))
		return (0);
	return (parse_centre_params(vect, tmp_ptr));
}

int	ft_insert_diameter(t_sphere *sphere, char **tmp_ptr)
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
			sphere->diameter = ft_atof(tmp);
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

int	ft_insert_color(t_color *color, char **tmp_ptr)
{
	if (!is_valid_format(*tmp_ptr, "COL"))
		return (0);
	return (parse_color_params(color, tmp_ptr));
}

int	insert_sphere_param(int param, t_sphere *sphere, char **tmp_ptr)
{
	if (param == 0)
	{
		if (!ft_insert_centre(&sphere->centre, tmp_ptr))
			return (0);
	}
	else if (param == 1)
	{
		if (!ft_insert_diameter(sphere, tmp_ptr))
			return (0);
	}
	else if (param == 2)
	{
		if (!ft_insert_color(&sphere->color, tmp_ptr))
			return (0);
	}
	return (1);
}

void	ft_create_sphere(t_scene *scene, t_object *obj, char **tmp)
{
	int			param;
	char		*tmp_ptr;
	t_sphere	*sphere;

	param = 0;
	tmp_ptr = *tmp;
	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	check_sphere_allocation(sphere, scene);
	while (param < NB_ATR_SPHERE && *tmp_ptr != '\0')
	{
		if (*tmp_ptr == ' ')
		{
			tmp_ptr++;
			continue ;
		}
		validate_sphere_new_element(tmp_ptr, sphere, scene);
		insert_sphereparam_or_exit(param, sphere, &tmp_ptr, scene);
		param++;
	}
	check_sphereparam_or_exit(param, sphere, tmp_ptr, scene);
	sphere->radius = sphere->diameter / 2.0;
	sphere->obj = obj;
	sphere->id = obj->id;
	obj->type = SPHERE;
	obj->ptr = sphere;
}
