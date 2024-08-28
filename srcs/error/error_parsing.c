/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:14:57 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:15:16 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	check_allocation(t_scene *scene)
{
	if (!scene->objects)
	{
		printf("Error: Failed to allocate memory for scene objects\n");
		free(scene->rt_file);
		free(scene->objects);
		exit(1);
	}
}

int	ft_error_nb_arg(void)
{
	printf("Error\nWrong number of arguments\n");
	exit(1);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc != 2)
		return (ft_error_nb_arg());
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) != 0)
	{
		printf("Error\nWrong file extension\n");
		exit(1);
	}
	return (0);
}

int	ft_error_open_file(void)
{
	printf("Error\nCannot open file\n");
	exit(1);
}

int	ft_error_file_empty(void)
{
	printf("Error\nFile is empty\n");
	exit(1);
}
