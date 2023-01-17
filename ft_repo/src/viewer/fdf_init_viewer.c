/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_viewer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/17 16:14:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_init_zoom_base(t_fdf *fdf)
{
	float	zoom_w;
	float	zoom_h;

	zoom_w = WIN_WIDTH * 0.67 / (fdf->map.size_x - 1);
	zoom_h = WIN_HEIGHT * 0.67 / (fdf->map.size_y - 1);
	fdf->viewer.zoom_base = fmin(zoom_w, zoom_h);
}

static void	fdf_init_z_scale_base(t_fdf *fdf)
{
	float	max_xy;

	if (fdf->map.dz == 0)
		fdf->viewer.z_scale_base = 1;
	else
	{
		max_xy = fmax(fdf->map.size_x, fdf->map.size_y);
		fdf->viewer.z_scale_base = max_xy / fdf->map.dz / 10;
	}
}

void	fdf_init_viewer(t_fdf *fdf)
{
	fdf_init_zoom_base(fdf);
	fdf_init_z_scale_base(fdf);
	fdf->viewer.z_cam = fmax(WIN_WIDTH, WIN_HEIGHT);
	fdf->viewer.perspective = 0;
	fdf->viewer.help = 0;
	fdf->viewer.color = DISABLED;
	fdf->viewer.render = WIREFRAME;
	fdf_set_view(fdf, 0);
}
