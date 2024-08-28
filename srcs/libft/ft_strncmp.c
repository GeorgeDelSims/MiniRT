/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:16:52 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:16:53 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	check1(unsigned char *b1, unsigned char *b2)
{
	if (*b1 - *b2 < 0)
		return (-1);
	else
		return (1);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*b1;
	unsigned char	*b2;

	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	while (n && *b1 != '\0' && *b2 != '\0')
	{
		if (*b1 != *b2)
			return (check1(b1, b2));
		b1++;
		b2++;
		n--;
	}
	if (n > 0)
	{
		if (*b1 - *b2 > 0)
			return (1);
		else if (*b1 - *b2 < 0)
			return (-1);
		return (0);
	}
	return (0);
}
