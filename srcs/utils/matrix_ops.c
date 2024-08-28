/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:55 by gsims             #+#    #+#             */
/*   Updated: 2024/08/20 11:25:05 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// utility function for the matrix multiplication
static double	multiply_util(double **m1, double **m2, size_t row, size_t col)
{
	double	result;
	size_t	i;

	result = 0;
	i = 0;
	while (i < 4)
	{
		result += (m1[row][i] * m2[i][col]);
		i++;
	}
	return (result);
}

// Matrix multiplication (only for 4x4 matrices)
// Careful, the order of the matrices makes a difference
// ORDER : scaling, rotation, translation
double	**matrix_mul(double **m1, double **m2)
{
	double	**res;
	size_t	row;
	size_t	col;

	res = matrix_alloc(4);
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			res[row][col] = multiply_util(m1, m2, row, col);
			col++;
		}
		row++;
	}
	return (res);
}

// Invert columns and rows of a matrix
// new matrix dynamically allocated
double	**matrix_transpose(double **matrix)
{
	double	**res;
	size_t	row;
	size_t	col;

	row = 0;
	res = matrix_alloc(4);
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			res[col][row] = matrix[row][col];
			col++;
		}
		row++;
	}
	return (res);
}

// scalar division, divides each element of a matrix by the given <div>
double	**scalar_div(double **matrix, double div, size_t size)
{
	double	**res;
	size_t	row;
	size_t	col;

	res = matrix_alloc(size);
	if (!res)
		return (NULL);
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			res[row][col] = matrix[row][col] / div;
			col++;
		}
		row++;
	}
	return (res);
}

// scalar multiplication, multiplies each element of a matrix by the given <mul>
double	**scalar_mul(double **matrix, double mul, size_t size)
{
	double	**res;
	size_t	row;
	size_t	col;

	res = matrix_alloc(size);
	if (!res)
		return (NULL);
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			res[row][col] = matrix[row][col] * mul;
			col++;
		}
		row++;
	}
	return (res);
}
