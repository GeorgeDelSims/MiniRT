/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:14:05 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:14:06 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Fonction qui initie la scene
void	ft_init_scene(t_scene *scene, int width, int height,
		int number_of_objects)
{
	scene->rt_file = NULL;
	scene->mlx = mlx_init();
	if (!scene->mlx)
	{
		perror("Failed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
	scene->win = mlx_new_window(scene->mlx, width, height, "MiniRT");
	if (!scene->win)
	{
		perror("Failed to create window\n");
		exit(EXIT_FAILURE);
	}
	scene->width = width;
	scene->height = height;
	scene->object_count = number_of_objects;
}
