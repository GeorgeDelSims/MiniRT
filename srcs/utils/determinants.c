/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:44 by gsims             #+#    #+#             */
/*   Updated: 2024/08/19 12:11:45 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// calculates the determinant of a 2x2 matrix
double	determinant2x2(double **m)
{
	return ((m[0][0] * m[1][1]) - (m[0][1] * m[1][0]));
}

// Function to calculate the determinant of a 3x3 matrix
double	determinant3x3(double **matrix)
{
	double	det;

	det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2]
			* matrix[2][1]) - matrix[0][1] * (matrix[1][0] * matrix[2][2]
			- matrix[1][2] * matrix[2][0]) + matrix[0][2] * (matrix[1][0]
			* matrix[2][1] - matrix[1][1] * matrix[2][0]);
	return (det);
}

// calculates determinant of 4x4 matrix
// multiplies all elements of first row by their cofactors
// and adds them together
double	determinant4x4(double **matrix)
{
	double	det;

	det = ((cofactor4x4(matrix, 0, 0) * matrix[0][0]) + (cofactor4x4(matrix, 0,
					1) * matrix[0][1]) + (cofactor4x4(matrix, 0, 2)
				* matrix[0][2]) + (cofactor4x4(matrix, 0, 3) * matrix[0][3]));
	return (det);
}

// Calculates the minor of a 3x3 matrix at given row and col
double	minor3x3(double **matrix, size_t row, size_t col)
{
	double	**temp;
	double	minor;

	temp = submatrix(matrix, row, col, 3);
	minor = determinant2x2(temp);
	matrix_free(temp, 2);
	return (minor);
}

// Calculates the minor of a 4x4 matrix at given row and col
double	minor4x4(double **matrix, size_t row, size_t col)
{
	double	**tmp;
	double	minor;

	tmp = submatrix(matrix, row, col, 4);
	minor = determinant3x3(tmp);
	matrix_free(tmp, 3);
	return (minor);
}
