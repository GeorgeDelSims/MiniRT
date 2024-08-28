/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:12:00 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:12:01 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// free matrix and all pointers within it
void	matrix_free(double **matrix, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

// Print function for any matrix (with a given size)
void	print_matrix(double **matrix, size_t size, char *name)
{
	size_t	row;
	size_t	col;

	printf("%s\n", name);
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			printf("| %f ", matrix[row][col]);
			col++;
		}
		printf("|\n");
		row++;
	}
	write(1, "\n", 1);
}

/*
// Checks if two matrixes are equal
// input the size of the matrix as well
bool	matrix_equal(double **m1, double **m2, size_t size)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			if (m1[row][col] != m2[row][col])
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}
*/
