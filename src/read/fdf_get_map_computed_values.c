/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_computed_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/11 09:54:18 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_get_map_computed_values(t_fdf *fdf)
{
	int		x;
	int		y;

	fdf->map.z_min = fdf->map.values[0][0].z;
	fdf->map.z_max = fdf->map.values[0][0].z;
	fdf->map.has_color = 0;
	x = 0;
	while (x < fdf->map.size_x)
	{
		y = 0;
		while (y < fdf->map.size_y)
		{
			fdf->map.z_min = fmin(fdf->map.z_min, fdf->map.values[x][y].z);
			fdf->map.z_max = fmax(fdf->map.z_max, fdf->map.values[x][y].z);
			if (fdf->map.values[x][y].color != -1)
				fdf->map.has_color = 1;
			y++;
		}
		x++;
	}
	fdf->map.dz = fdf->map.z_max - fdf->map.z_min;
}
