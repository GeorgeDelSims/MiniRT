/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:16:40 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:16:41 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	parse_integer_part(char *str, int *i)
{
	double	res;

	res = 0;
	while (str[*i] && str[*i] != '.' && str[*i] != ',' && str[*i] != ' ')
	{
		res = res * 10 + str[*i] - '0';
		(*i)++;
	}
	return (res);
}

double	parse_fractional_part(char *str, int *i)
{
	double	res;
	double	divisor;

	res = 0;
	divisor = 1;
	if (str[*i] == '.')
		(*i)++;
	while (str[*i] && str[*i] != ',' && str[*i] != ' ')
	{
		res = res * 10 + str[*i] - '0';
		divisor *= 10;
		(*i)++;
	}
	return (res / divisor);
}

double	ft_atof(char *str)
{
	double	res;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	res = parse_integer_part(str, &i);
	res += parse_fractional_part(str, &i);
	return (res * sign);
}
