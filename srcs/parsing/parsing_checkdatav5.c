/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkdatav5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:40:58 by rtauzin           #+#    #+#             */
/*   Updated: 2024/08/26 19:16:19 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	is_invalid_coordinate(char *str, int i)
{
	if ((str[i] == ',' && (str[i + 1] == ',' || str[i + 1] == '.'))
		|| (str[i] == '.' && i == 0) || (str[i] == '.' && !check_isdigit(str[i
					+ 1])) || (str[i] == '-' && !check_isdigit(str[i + 1]))
		|| (check_isdigit(str[i]) && (str[i + 1] == '-')))
	{
		printf("Error\n Invalid value\n");
		exit(1);
	}
	return (0);
}

void	check_orientation_range(float orient)
{
	if (orient < -1.0 || orient > 1.0)
	{
		printf("Error\n Orientation must be in range [-1.0,1.0]\n");
		exit(1);
	}
}

int	check_comma(char *str, int i, int *commacount)
{
	if (str[i] == ',')
	{
		(*commacount)++;
		i++;
	}
	return (i);
}
