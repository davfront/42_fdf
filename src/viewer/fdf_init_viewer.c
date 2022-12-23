/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_viewer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 07:46:14 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_viewer(t_fdf *fdf)
{
	float		x_scale;
	float		y_scale;

	x_scale = (WIN_WIDTH * 0.8 / (fdf->map.size_x - 1));
	y_scale = (WIN_HEIGHT * 0.8 / (fdf->map.size_y - 1));
	fdf->zoom = fmin(x_scale, y_scale);
	fdf->z_scale = 1;

	fdf->x0 = (WIN_WIDTH - (fdf->map.size_x - 1) * fdf->zoom) / 2;
	fdf->y0 = (WIN_HEIGHT - (fdf->map.size_y - 1) * fdf->zoom) / 2;

	fdf->rx = PI / 5;
	fdf->ry = PI / 4;

	fdf_init_mt(fdf);
}
