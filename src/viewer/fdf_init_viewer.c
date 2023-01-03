/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_viewer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/03 10:40:55 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_mt(t_fdf *fdf, int view)
{
	float		zoom;

	zoom = (WIN_WIDTH * 0.67 / (fdf->map.size_x - 1));
	zoom = fmin(zoom, (WIN_HEIGHT * 0.67 / (fdf->map.size_y - 1)));
	fdf_matrix_init(fdf->mt);
	fdf_matrix_translate(fdf->mt, -fdf->map.size_x / 2, -fdf->map.size_y / 2);
	fdf_matrix_scale(fdf->mt, zoom, zoom, zoom);
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
	fdf_matrix_translate(fdf->mt, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void	fdf_init_viewer(t_fdf *fdf)
{
	fdf->opt.perspective = 0;
	fdf->opt.help = 0;
	fdf->opt.solid = 0;
	fdf_init_mt(fdf, 0);
}
