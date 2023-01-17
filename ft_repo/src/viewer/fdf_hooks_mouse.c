/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks_mouse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/17 16:35:55 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_on_mouse_down(int button, int x, int y, t_fdf *fdf)
{
	t_viewer	vwr;

	vwr = fdf->viewer;
	if (button == MOUSE_SCROLL_UP && vwr.zoom < \
		vwr.zoom_base * fmax(fdf->map.size_x, fdf->map.size_y) / 5)
		fdf->viewer.zoom *= 1.1;
	if (button == MOUSE_SCROLL_DOWN && vwr.zoom > vwr.zoom_base / 20)
		fdf->viewer.zoom /= 1.1;
	if (button == MOUSE_LEFT)
		fdf->ui.mouse_left_btn = 1;
	if (button == MOUSE_RIGHT)
		fdf->ui.mouse_right_btn = 1;
	fdf->ui.mouse_x0 = x;
	fdf->ui.mouse_y0 = y;
	fdf->ui.mouse_dx = 0;
	fdf->ui.mouse_dy = 0;
	return (0);
}

int	fdf_on_mouse_up(int button, int x, int y, t_fdf *fdf)
{
	fdf->ui.mouse_dx = x - fdf->ui.mouse_x0;
	fdf->ui.mouse_dy = y - fdf->ui.mouse_y0;
	if (button == MOUSE_LEFT)
	{
		fdf->viewer.cx += fdf->ui.mouse_dx;
		fdf->viewer.cy += fdf->ui.mouse_dy;
		fdf->ui.mouse_left_btn = 0;
	}
	if (button == MOUSE_RIGHT)
	{
		fdf_matrix_rotate_y(fdf->viewer.rot, -fdf->ui.mouse_dx * PI / 500);
		fdf_matrix_rotate_x(fdf->viewer.rot, fdf->ui.mouse_dy * PI / 500);
		fdf->ui.mouse_right_btn = 0;
	}
	fdf->ui.mouse_x0 = 0;
	fdf->ui.mouse_y0 = 0;
	fdf->ui.mouse_dx = 0;
	fdf->ui.mouse_dy = 0;
	return (0);
}

int	fdf_on_mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->ui.mouse_dx = x - fdf->ui.mouse_x0;
	fdf->ui.mouse_dy = y - fdf->ui.mouse_y0;
	return (0);
}
