/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_viewer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/24 08:53:15 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_mt(t_fdf *fdf)
{
	float		zoom;

	zoom = (WIN_WIDTH * 0.8 / (fdf->map.size_x - 1));
	zoom = fmin(zoom, (WIN_HEIGHT * 0.8 / (fdf->map.size_y - 1)));
	fdf_matrix_init(fdf->mt);
	fdf_matrix_translate(fdf->mt, -fdf->map.size_x / 2, -fdf->map.size_y / 2);
	fdf_matrix_scale(fdf->mt, zoom, zoom, zoom);
	fdf_matrix_rotate_x(fdf->mt, -PI / 2);
	fdf_matrix_rotate_y(fdf->mt, PI / 4);
	fdf_matrix_rotate_x(fdf->mt, PI / 5);
	fdf_matrix_translate(fdf->mt, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void	fdf_init_viewer(t_fdf *fdf)
{
	fdf->opt.perspective = 0;
	fdf_init_mt(fdf);
}
