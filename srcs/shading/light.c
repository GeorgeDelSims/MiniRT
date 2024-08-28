/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:05:57 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:08:21 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// creates a light source struct with position (POINT)
// and a light of intensity (1,1,1)
t_light	create_light_source(t_tuple position, t_color intensity)
{
	t_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}
