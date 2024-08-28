/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:52 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:11:53 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Allocates the memory for matrix of given size
double	**matrix_alloc(size_t size)
{
	double	**matrix;
	size_t	row;

	matrix = (double **)malloc(sizeof(double *) * size);
	if (!matrix)
		return (NULL);
	row = 0;
	while (row < size)
	{
		matrix[row] = (double *)malloc(sizeof(double) * size);
		if (!matrix[row])
		{
			while (row > 0)
			{
				row--;
				free(matrix[row]);
			}
			free(matrix);
			return (NULL);
		}
		row++;
	}
	return (matrix);
}

// Creates Matrix full of single value
double	**fill_matrix(double value, size_t size)
{
	double	**matrix;
	size_t	row;
	size_t	col;

	matrix = matrix_alloc(size);
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			matrix[row][col] = value;
			col++;
		}
		row++;
	}
	return (matrix);
}

// Creates Matrix full of single value
double	**test_matrix(double value, size_t size)
{
	double	**matrix;
	size_t	row;
	size_t	col;

	matrix = matrix_alloc(size);
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			matrix[row][col] = value++;
			col++;
		}
		row++;
	}
	return (matrix);
}

// Creates identity matrix
double	**identity_matrix(size_t size)
{
	double	**matrix;
	size_t	row;
	size_t	col;

	matrix = matrix_alloc(size);
	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			if (row == col)
				matrix[row][col] = 1;
			else
				matrix[row][col] = 0;
			col++;
		}
		row++;
	}
	return (matrix);
}

/*
// Testing  function for creating custom matrices (4x4)
double	**create_matrix(double a1, double a2, double a3, double a4,\
						double b1, double b2, double b3, double b4,\
						double c1, double c2, double c3, double c4,\
						double d1, double d2, double d3, double d4)
{
	double	**m;

	m = matrix_alloc(4);
	m[0][0] = a1;
	m[0][1] = a2;
	m[0][2] = a3;
	m[0][3] = a4;
	m[1][0] = b1;
	m[1][1] = b2;
	m[1][2] = b3;
	m[1][3] = b4;
	m[2][0] = c1;
	m[2][1] = c2;
	m[2][2] = c3;
	m[2][3] = c4;
	m[3][0] = d1;
	m[3][1] = d2;
	m[3][2] = d3;
	m[3][3] = d4;
	return (m);
}

*/
