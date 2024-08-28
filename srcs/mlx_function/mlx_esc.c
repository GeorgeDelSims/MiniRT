/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_esc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:16:57 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:16:58 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	exit_program(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	free_all_objects(scene);
	exit(0);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == 53 || keycode == 65307)
		exit_program(scene);
	return (0);
}
