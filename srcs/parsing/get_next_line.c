/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:03:19 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:03:20 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static char	*ft_read_error(char **storage)
{
	free(*storage);
	*storage = NULL;
	return (NULL);
}

static char	*ft_read_and_store(int fd, char *buf, char **storage)
{
	char	*storage_tmp;
	int		read_row;

	read_row = 1;
	while (read_row > 0)
	{
		read_row = read(fd, buf, BUFFER_SIZE);
		if (read_row == -1)
			return (ft_read_error(storage));
		else if (read_row == 0)
			break ;
		buf[read_row] = '\0';
		if (!*storage)
			*storage = ft_strdup("");
		storage_tmp = *storage;
		*storage = ft_strjoin(storage_tmp, buf);
		free(storage_tmp);
		storage_tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (*storage);
}

static char	*ft_extract_row(char *row)
{
	size_t	count;
	char	*new_storage;

	count = 0;
	while (row[count] != '\n' && row[count] != '\0')
		count++;
	if (row[count] == '\0')
		return (NULL);
	new_storage = ft_substr(row, count + 1, ft_strlen(row) - count);
	if (new_storage && *new_storage == '\0')
	{
		free(new_storage);
		new_storage = NULL;
	}
	row[count + 1] = '\0';
	return (new_storage);
}

char	*ft_get_next_line(int fd)
{
	char		*row;
	char		buf[BUFFER_SIZE + 1];
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	row = ft_read_and_store(fd, buf, &storage);
	if (!row)
		return (NULL);
	storage = ft_extract_row(row);
	return (row);
}
