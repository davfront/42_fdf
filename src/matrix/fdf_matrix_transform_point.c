/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_transform_point.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 19:20:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_matrix_transform_point(float point[4], float matrix[4][4])
{
	int		i;
	int		j;
	float	result[4];

	i = 0;
	while (i < 4)
	{
		result[i] = 0.0;
		j = 0;
		while (j < 4)
		{
			result[i] += point[j] * matrix[j][i];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		point[i] = result[i];
		i++;
	}
}
