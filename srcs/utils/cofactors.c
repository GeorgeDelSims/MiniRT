/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cofactors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:41 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:13:46 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Determines the cofactor of a 3x3 matrix at given row and col
// cofactor = minor, unless row + col is an odd number
// in which case, cofactor = -minor
double	cofactor3x3(double **matrix, size_t row, size_t col)
{
	if ((row + col) % 2 != 0)
		return ((-1 * minor3x3(matrix, row, col)));
	else
		return (minor3x3(matrix, row, col));
}

// Determines the cofactor of a 4x4 matrix at given row and col
double	cofactor4x4(double **matrix, size_t row, size_t col)
{
	if ((row + col) % 2 != 0)
		return ((-1 * minor4x4(matrix, row, col)));
	else
		return (minor4x4(matrix, row, col));
}

// helper function for cofactor matrix
// returns each row of cofactors
// only works for 4x4 matrices
static double	*get_cofactor_row(double **matrix, size_t index)
{
	double	*row;
	size_t	i;

	row = malloc(sizeof(double) * 4);
	if (!row)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		row[i] = cofactor4x4(matrix, index, i);
		i++;
	}
	return (row);
}

// returns a matrix of cofactors of each value of the original matrix
double	**cofactor_matrix(double **matrix)
{
	double	**cof_matrix;
	size_t	i;

	cof_matrix = malloc(sizeof(double *) * 4);
	if (!cof_matrix)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		cof_matrix[i] = get_cofactor_row(matrix, i);
		i++;
	}
	return (cof_matrix);
}
