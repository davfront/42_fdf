/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_multiply.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 19:20:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_matrix_multiply(float m1[4][4], float m2[4][4])
{
	int		i;
	int		j;
	int		k;
	float	result[4][4];

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = 0.0;
			k = 0;
			while (k < 4)
			{
				result[i][j] += m1[i][k] * m2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	fdf_matrix_copy(m1, result);
}
