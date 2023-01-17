/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/17 16:13:02 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_init_center(t_fdf *fdf)
{
	fdf->viewer.cx = WIN_WIDTH / 2;
	fdf->viewer.cy = WIN_HEIGHT / 2;
}

void	fdf_set_view(t_fdf *fdf, int view)
{
	fdf_init_center(fdf);
	fdf->viewer.zoom = fdf->viewer.zoom_base;
	fdf->viewer.z_scale = fdf->viewer.z_scale_base;
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
