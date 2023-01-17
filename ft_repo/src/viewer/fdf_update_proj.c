/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_update_proj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/17 16:21:58 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_update_proj(t_fdf *fdf)
{
	float		p[4][4];
	t_map		m;
	t_viewer	v;
	t_ui		ui;

	m = fdf->map;
	v = fdf->viewer;
	ui = fdf->ui;
	fdf_matrix_init(p);
	fdf_matrix_translate(p, (1 - (float)m.size_x) / 2, (1 - (float)m.size_y) / 2);
	fdf_matrix_scale(p, v.zoom, v.zoom, v.zoom * v.z_scale);
	fdf_matrix_multiply(p, v.rot);
	fdf_matrix_rotate_y(p, -ui.mouse_dx * ui.mouse_right_btn * PI / 500);
	fdf_matrix_rotate_x(p, ui.mouse_dy * ui.mouse_right_btn * PI / 500);
	fdf_matrix_translate(p, v.cx + ui.mouse_dx * ui.mouse_left_btn, 
		v.cy + ui.mouse_dy * ui.mouse_left_btn);
	ft_memcpy(fdf->viewer.proj, p, sizeof(p));
}
