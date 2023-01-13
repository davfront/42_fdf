/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/13 15:09:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_init_center(t_fdf *fdf)
{
	fdf->viewer.cx = WIN_WIDTH / 2;
	fdf->viewer.cy = WIN_HEIGHT / 2;
}

static void	fdf_init_zoom(t_fdf *fdf)
{
	float	zoom_w;
	float	zoom_h;

	zoom_w = WIN_WIDTH * 0.67 / (fdf->map.size_x - 1);
	zoom_h = WIN_HEIGHT * 0.67 / (fdf->map.size_y - 1);
	fdf->viewer.zoom = fmin(zoom_w, zoom_h);
}

static void	fdf_init_z_scale(t_fdf *fdf)
{
	float	max_xy;

	max_xy = fmax(fdf->map.size_x, fdf->map.size_y);
	fdf->viewer.z_scale = max_xy / fdf->map.dz / 10;
}

void	fdf_set_view(t_fdf *fdf, int view)
{
	fdf_init_center(fdf);
	fdf_init_zoom(fdf);
	fdf_init_z_scale(fdf);
	fdf_matrix_init(fdf->viewer.rot);
	if (view == 2)
	{
		fdf_matrix_rotate_x(fdf->viewer.rot, -PI / 2);
	}
	if (view == 3)
	{
		fdf_matrix_rotate_x(fdf->viewer.rot, -PI / 2);
		fdf_matrix_rotate_y(fdf->viewer.rot, -PI / 2);
	}
	if (view == 0)
	{
		fdf_matrix_rotate_x(fdf->viewer.rot, -PI / 2);
		fdf_matrix_rotate_y(fdf->viewer.rot, PI / 4);
		fdf_matrix_rotate_x(fdf->viewer.rot, PI / 5);
	}
}
