/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:14:14 by gsims             #+#    #+#             */
/*   Updated: 2024/08/26 17:51:20 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	(void)argv;
	ft_check_args(argc, argv);
	ft_alloc_scene(&scene);
	ft_open_file_rt(&scene, argv[1]);
	ft_clean_file_rt(&scene);
	ft_parsing_rt(&scene);
	ft_init_scene(&scene, WIDTH, HEIGHT, scene.object_count);
	cast_rays(&scene);
	mlx_key_hook(scene.win, key_hook, &scene);
	mlx_hook(scene.win, 17, 0, (void *)exit, 0);
	mlx_loop(scene.mlx);
	return (0);
}
