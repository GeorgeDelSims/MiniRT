/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_rt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:22 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:23 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_scene	ft_alloc_scene(t_scene *scene)
{
	scene->rt_file = NULL;
	scene->objects = NULL;
	scene->mlx = NULL;
	scene->win = NULL;
	return (*scene);
}

void	append_line_to_content(char **file_content, char *line)
{
	char	*tmp;

	if (*file_content == NULL)
		*file_content = ft_strdup(line);
	else
	{
		tmp = *file_content;
		*file_content = ft_strjoin(tmp, line);
		free(tmp);
	}
}

void	ft_open_file_rt(t_scene *scene, char *rt_file)
{
	int		fd;
	char	*line;
	char	*file_content;

	file_content = NULL;
	fd = open(rt_file, O_RDONLY);
	if (fd == -1)
		ft_error_open_file();
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		append_line_to_content(&file_content, line);
		free(line);
		line = ft_get_next_line(fd);
	}
	if (!file_content)
		ft_error_file_empty();
	scene->rt_file = file_content;
	close(fd);
}

void	ft_clean_file_rt(t_scene *scene)
{
	char	*line;
	int		i;

	line = scene->rt_file;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || line[i] == '\n' || line[i] == '\r'
			|| line[i] == '\v' || line[i] == '\f')
			line[i] = ' ';
		i++;
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' && line[i + 1] == ' ')
		{
			ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i + 1]) + 1);
			i--;
		}
		i++;
	}
	scene->rt_file = line;
}
