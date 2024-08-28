/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   submatrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:12:06 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:38:43 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

typedef struct s_info
{
	size_t		i;
	size_t		sub_row;
	size_t		size;
	size_t		r_sk;
	size_t		c_sk;	
}				t_info;

// bool helper function
static bool	skip_index(size_t index, size_t skip)
{
	return (index == skip);
}

// This function needs to be refactored in order to have less arguments
static void	copy_row(double **src, double **dst, t_info info)
{
	size_t	j;
	size_t	sub_col;

	j = 0;
	sub_col = 0;
	while (j < info.size)
	{
		if (!skip_index(j, info.c_sk))
		{
			dst[info.sub_row][sub_col] = src[info.i][j];
			sub_col++;
		}
		j++;
	}
}

// allocates the memory for a submatrix
static double	**alloc_sub(double **m, size_t size, size_t r_sk, size_t c_sk)
{
	double	**res;
	t_info	info;

	info.i = 0;
	info.sub_row = 0;
	info.size = size;
	info.r_sk = r_sk;
	info.c_sk = c_sk;
	res = matrix_alloc(info.size - 1);
	if (!res)
		return (NULL);
	while (info.i < info.size)
	{
		if (!skip_index(info.i, info.r_sk))
		{
			copy_row(m, res, info);
			info.sub_row++;
		}
		info.i++;
	}
	return (res);
}

// Main submatrix function that removes a row and a column from a m
double	**submatrix(double **m, size_t row, size_t col, size_t size)
{
	if (row >= size || col >= size)
		return (NULL);
	return (alloc_sub(m, size, row, col));
}
