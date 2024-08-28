/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:06:09 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:06:10 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// compute the reflection vector according to the normal vector
t_tuple	reflect(t_tuple in, t_tuple normal)
{
	t_tuple	out;
	t_tuple	scaled;
	double	dot;

	normal = normalise(normal);
	dot = dot_prod(in, normal);
	scaled = scale_tuple(normal, (2 * dot));
	out = subtr_tuple(in, scaled);
	return (out);
}
