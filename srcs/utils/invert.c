/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsims <gsims@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:11:49 by gsims             #+#    #+#             */
/*   Updated: 2024/08/20 11:29:21 by gsims            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Checks if a matrix is invertible or not
// if the deteminant is equal to 0, it cannot be inverted
bool	is_invertible(double **matrix)
{
	if (determinant4x4(matrix) == 0)
		return (false);
	else
		return (true);
}

// inverts a matrix by creating a cofactor matrix, transposing it
// and dividing it by the original determinant
double	**invert_matrix(double **matrix)
{
	double	**tmp;
	double	**tmp2;
	double	det;

	det = determinant4x4(matrix);
	tmp = cofactor_matrix(matrix);
	tmp2 = matrix_transpose(tmp);
	matrix_free(tmp, 4);
	tmp = scalar_div(tmp2, det, 4);
	matrix_free(tmp2, 4);
	return (tmp);
}
