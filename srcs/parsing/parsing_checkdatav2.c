/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkdatav2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:52 by gsims             #+#    #+#             */
/*   Updated: 2024/08/26 18:21:40 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_valid_ambient_lighting(char *str)
{
	double	ambient_light;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		is_invalid_coordinate(str, i);
		i++;
	}
	ambient_light = ft_atof(str);
	if (ambient_light < 0.0 || ambient_light > 1.0)
	{
		printf("Error\n Ambient lighting ratio must be in range [0.0,1.0]\n");
		exit(1);
	}
}

void	check_valid_fov(char *str)
{
	double	fov;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		is_invalid_coordinate(str, i);
		i++;
	}
	fov = ft_atof(str);
	if (fov < 0.0 || fov > 180.0)
	{
		printf("Error\n Field of view must be in range [0.0,180.0]\n");
		exit(1);
	}
}

void	check_valid_brightness(char *str)
{
	double	brightness;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		is_invalid_coordinate(str, i);
		i++;
	}
	brightness = ft_atof(str);
	if (brightness < 0.0 || brightness > 1.0)
	{
		printf("Error\n Brightness must be in range [0.0,1.0]\n");
		exit(1);
	}
}

void	check_valid_center(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != ' ')
	{
		is_invalid_coordinate(str, i);
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		printf("Error\n Invalid center coordinates\n");
		exit(1);
	}
}

void	check_valid_vector(char *str)
{
	int		i;
	int		nbvalue;
	int		commacount;
	double	orient;

	i = 0;
	nbvalue = 0;
	commacount = 0;
	orient = 0.0;
	while (str[i] && str[i] != ' ' && nbvalue < 3)
	{
		is_invalid_coordinate(str, i);
		orient = ft_atof(&str[i]);
		check_orientation_range(orient);
		while (check_isdigit(str[i]) || str[i] == '.' || str[i] == '-')
			i++;
		check_consecutive_commas(str, i);
		i = check_comma(str, i, &commacount);
		nbvalue++;
	}
	check_comma_count(commacount);
}
