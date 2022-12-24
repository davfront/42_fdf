/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_zminmax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/24 15:46:11 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_get_map_zminmax(t_fdf *fdf)
{
	int		x;
	int		y;

	fdf->map.z_min = fdf->map.values[0][0];
	fdf->map.z_max = fdf->map.values[0][0];
	x = 0;
	while (x < fdf->map.size_x)
	{
		y = 0;
		while (y < fdf->map.size_y)
		{
			fdf->map.z_min = fmin(fdf->map.z_min, fdf->map.values[x][y]);
			fdf->map.z_max = fmax(fdf->map.z_max, fdf->map.values[x][y]);
			y++;
		}
		x++;
	}
}
