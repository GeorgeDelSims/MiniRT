/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkdatav3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:55 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:56 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	advance_through_number(char **tmp_ptr)
{
	char	*tmp;

	tmp = *tmp_ptr;
	while ((*tmp >= '0' && *tmp <= '9') || *tmp == '.' || *tmp == '-')
		tmp++;
	*tmp_ptr = tmp;
}

int	check_valid_param(int param_accepted, int param_count)
{
	if (param_accepted != param_count)
	{
		printf("Error\n Invalid number of parameters\n");
		return (0);
	}
	return (1);
}

int	is_new_element(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n')
	{
		str++;
	}
	if (*str == '\0')
		return (1);
	return (ft_strncmp(str, "A", 1) == 0 || ft_strncmp(str, "C", 1) == 0
		|| ft_strncmp(str, "L", 1) == 0 || ft_strncmp(str, "sp", 2) == 0
		|| ft_strncmp(str, "pl", 2) == 0 || ft_strncmp(str, "cy", 2) == 0);
}

void	check_valid_diameter(char *str)
{
	double	diameter;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		is_invalid_coordinate(str, i);
		i++;
	}
	diameter = ft_atof(str);
	if (diameter <= 0.0)
	{
		printf("Error\n Diameter must be positive\n");
		exit(1);
	}
}

int	is_wrong_float(char *str)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	while (str[i] && str[i] != ' ' && str[i] != ',')
	{
		if ((str[i] == '.' && !check_isdigit(str[i + 1])))
		{
			printf("Error\n Invalid format des donnees float\n");
			exit(1);
		}
		if (str[i] == '.')
		{
			point++;
		}
		if (point > 1)
		{
			printf("Error\n Invalid format des donnees nombre de point float\n");
			exit(1);
		}
		i++;
	}
	return (0);
}
