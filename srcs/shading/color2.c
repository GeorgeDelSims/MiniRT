/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:05:44 by gsims             #+#    #+#             */
/*   Updated: 2024/08/20 12:05:42 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// convert a color struct to an integer value
int	col_to_int(t_color color)
{
	int	red;
	int	green;
	int	blue;

	red = (int)(color.red * 255.0);
	green = (int)(color.green * 255.0);
	blue = (int)(color.blue * 255.0);
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
	return ((red << 16) | (green << 8) | blue);
}

// testing print function for a t_color struct
void	print_color(t_color color)
{
	printf("red : %f\n", color.red);
	printf("green : %f\n", color.green);
	printf("blue : %f\n", color.blue);
}
