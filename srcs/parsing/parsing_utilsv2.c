/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilsv2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:43 by gsims             #+#    #+#             */
/*   Updated: 2024/08/24 12:14:30 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <stdio.h>
#include <unistd.h>

int	parse_color_params(t_color *color, char **tmp_ptr)
{
	int		param;
	char	*tmp;

	param = 0;
	tmp = *tmp_ptr;
	while (param < 3 && *tmp != '\0')
	{
		if (*tmp == ' ')
			break ;
		if (*tmp == ',')
			tmp++;
		else
		{
			if (param == 0)
				color->red = ft_atof(tmp) / 255;
			else if (param == 1)
				color->green = ft_atof(tmp) / 255;
			else if (param == 2)
				color->blue = ft_atof(tmp) / 255;
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

int	parse_centre_params(t_tuple *vect, char **tmp_ptr)
{
	int		param;
	char	*tmp;

	param = 0;
	tmp = *tmp_ptr;
	while (param < 3 && *tmp != '\0')
	{
		if (*tmp == ' ')
			break ;
		if (*tmp == ',')
			tmp++;
		else
		{
			if (param == 0)
				vect->x = ft_atof(tmp);
			else if (param == 1)
				vect->y = ft_atof(tmp);
			else if (param == 2)
				vect->z = ft_atof(tmp);
			param++;
			advance_through_number(&tmp);
		}
	}
	*tmp_ptr = tmp;
	return (1);
}

void	check_first_element(char **tmp, t_scene *scene)
{
	if (!is_new_element(*tmp))
	{
		printf("Error\n Invalid format des donnees first element\n");
		free(scene->objects);
		free(scene->rt_file);
		exit(1);
	}
}
