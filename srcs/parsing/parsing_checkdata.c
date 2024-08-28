/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkdata.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:49 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:50 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	check_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_separator(char *str)
{
	return (ft_strncmp(str, "A", 1) == 0 || ft_strncmp(str, "C", 1) == 0
		|| ft_strncmp(str, "L", 1) == 0);
}

int	is_object(char *str)
{
	return (ft_strncmp(str, "sp", 2) == 0 || ft_strncmp(str, "pl", 2) == 0
		|| ft_strncmp(str, "cy", 2) == 0);
}

int	check_valid_digit(char *str)
{
	if (is_separator(str))
		return (0);
	else if (is_object(str))
		return (1);
	else if (is_wrong_float(str))
		return (1);
	else if (!check_isdigit(*str) && *str != '.' && *str != '-' && *str != ' '
		&& *str != ',')
	{
		printf("Error\n Invalid format des donnees sur le format des digits\n");
		exit(1);
	}
	return (0);
}

int	is_valid_format(char *str, char *id)
{
	if (ft_strncmp(id, "AMB", 3) == 0)
		check_valid_ambient_lighting(str);
	if (ft_strncmp(id, "COL", 3) == 0)
		check_valid_color(str);
	if (ft_strncmp(id, "FOV", 3) == 0)
		check_valid_fov(str);
	if (ft_strncmp(id, "BRI", 3) == 0)
		check_valid_brightness(str);
	if (ft_strncmp(id, "CEN", 3) == 0)
		check_valid_center(str);
	if (ft_strncmp(id, "DIA", 3) == 0)
		check_valid_diameter(str);
	if (ft_strncmp(id, "VEC", 3) == 0)
		check_valid_vector(str);
	while (*str)
	{
		if (check_valid_digit(str) == 1)
			str++;
		str++;
	}
	return (1);
}
