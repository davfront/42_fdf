/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_viewer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 12:27:25 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_mt(t_fdf *fdf, int view)
{
	fdf_matrix_init(fdf->mt);
	if (view == 2)
	{
		fdf_matrix_rotate_x(fdf->mt, -PI / 2);
	}
	if (view == 3)
	{
		fdf_matrix_rotate_x(fdf->mt, -PI / 2);
		fdf_matrix_rotate_y(fdf->mt, -PI / 2);
	}
	if (view == 0)
	{
		fdf_matrix_rotate_x(fdf->mt, -PI / 2);
		fdf_matrix_rotate_y(fdf->mt, PI / 4);
		fdf_matrix_rotate_x(fdf->mt, PI / 5);
	}
}

void	fdf_init_viewer(t_fdf *fdf)
{
	fdf->opt.perspective = 0;
	fdf->opt.help = 0;
	fdf->opt.solid = 0;
	fdf->ui.key_space = 0;
	fdf->ui.key_z = 0;
	fdf->ui.mouse_x0 = 0;
	fdf->ui.mouse_y0 = 0;
	fdf->ui.mouse_dx = 0;
	fdf->ui.mouse_dy = 0;
	fdf->ui.mouse_left_btn = 0;
	fdf->ui.mouse_right_btn = 0;
	fdf->cx = WIN_WIDTH / 2;
	fdf->cy = WIN_HEIGHT / 2;
	fdf->zoom = (WIN_WIDTH * 0.67 / (fdf->map.size_x - 1));
	fdf->zoom = fmin(fdf->zoom, (WIN_HEIGHT * 0.67 / (fdf->map.size_y - 1)));
	fdf->z_scale = fmax(fdf->map.size_x, fdf->map.size_y) / fdf->map.dz / 5;
	fdf_init_mt(fdf, 0);
}
