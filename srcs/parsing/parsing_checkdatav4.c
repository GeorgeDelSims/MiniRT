/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checkdatav4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtauzin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:40:58 by rtauzin           #+#    #+#             */
/*   Updated: 2024/08/24 19:41:01 by rtauzin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_invalid_character(char c)
{
	if (c != ' ' && c != ',' && c != '\0' && is_separator(&c) == 0 && c != 's'
		&& c != 'p' && c != 'c')
	{
		printf("Error\n Invalid character '%c' in input\n", c);
		exit(1);
	}
}

void	validate_color_value(int color)
{
	if (color < 0 || color > 255)
	{
		printf("Error\n Color values must be in range [0,255]\n");
		exit(1);
	}
}

void	check_consecutive_commas(char *str, int i)
{
	if (str[i] == ',' && str[i + 1] == ',')
	{
		printf("Error\n Consecutive commas are not allowed\n");
		exit(1);
	}
}

void	check_comma_count(int commacount)
{
	if (commacount != 2)
	{
		printf("Error\n Invalid color format\n");
		exit(1);
	}
}

void	check_valid_color(char *str)
{
	int	color;
	int	nbcolor;
	int	commacount;
	int	i;

	nbcolor = 0;
	commacount = 0;
	i = 0;
	while (nbcolor < 3 && str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		color = ft_atoi(&str[i]);
		validate_color_value(color);
		while (check_isdigit(str[i]))
			i++;
		check_invalid_character(str[i]);
		check_consecutive_commas(str, i);
		i = check_comma(str, i, &commacount);
		nbcolor++;
	}
	check_comma_count(commacount);
}
