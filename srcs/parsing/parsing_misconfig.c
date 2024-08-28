/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misconfig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:04:15 by gsims             #+#    #+#             */
/*   Updated: 2024/08/24 13:11:29 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	check_nb_objects(char *rt_file)
{
	int		count_sp;
	int		count_pl;
	int		count_cy;
	char	*tmp;

	count_sp = 0;
	count_pl = 0;
	count_cy = 0;
	tmp = rt_file;
	while (*tmp)
	{
		if (ft_strncmp(tmp, "sp", 2) == 0)
			count_sp++;
		else if (ft_strncmp(tmp, "pl", 2) == 0)
			count_pl++;
		else if (ft_strncmp(tmp, "cy", 2) == 0)
			count_cy++;
		tmp++;
	}
	if (count_sp == 0 && count_pl == 0 && count_cy == 0)
		return (0);
	return (1);
}

int	check_nb_elements(char *rt_file)
{
	int		counta;
	int		countc;
	int		countl;
	char	*tmp;

	counta = 0;
	countc = 0;
	countl = 0;
	tmp = rt_file;
	while (*tmp)
	{
		if (ft_strncmp(tmp, "A", 1) == 0)
			counta++;
		else if (ft_strncmp(tmp, "C", 1) == 0)
			countc++;
		else if (ft_strncmp(tmp, "L", 1) == 0)
			countl++;
		tmp++;
	}
	if (counta != 1 || countc != 1 || countl != 1)
		return (0);
	return (1);
}

void	check_misconfiguration_rt_file(t_scene *scene)
{
	if (!check_nb_objects(scene->rt_file))
	{
		printf("Error\nNumber of objects in .rt file\n");
		free(scene->rt_file);
		free(scene->objects);
		exit(1);
	}
	if (!check_nb_elements(scene->rt_file))
	{
		printf("Error\nNumber of elements in .rt file\n");
		free(scene->rt_file);
		free(scene->objects);
		exit(1);
	}
}
