/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/16 20:28:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_on_arrow_down(int keycode, t_fdf *fdf)
{
	if (fdf->ui.key_space)
	{
		if (keycode == KEY_LEFT)
			fdf->viewer.cx += -10;
		if (keycode == KEY_RIGHT)
			fdf->viewer.cx += 10;
		if (keycode == KEY_UP)
			fdf->viewer.cy += -10;
		if (keycode == KEY_DOWN)
			fdf->viewer.cy += 10;
	}
	else
	{
		if (keycode == KEY_LEFT)
			fdf_matrix_rotate_y(fdf->viewer.rot, PI / 50);
		if (keycode == KEY_RIGHT)
			fdf_matrix_rotate_y(fdf->viewer.rot, -PI / 50);
		if (keycode == KEY_UP)
			fdf_matrix_rotate_x(fdf->viewer.rot, -PI / 50);
		if (keycode == KEY_DOWN)
			fdf_matrix_rotate_x(fdf->viewer.rot, PI / 50);
	}
}

void	fdf_on_plus_minus_down(int keycode, t_fdf *fdf)
{
	float	z_scale_base;

	z_scale_base = fmax(fdf->map.size_x, fdf->map.size_y) / fdf->map.dz / 10;
	if (fdf->ui.key_z)
	{
		if (keycode == KEY_PLUS && fdf->viewer.z_scale < z_scale_base * 8)
			fdf->viewer.z_scale *= 1.1;
		if (keycode == KEY_MINUS && fdf->viewer.z_scale > z_scale_base / 8)
			fdf->viewer.z_scale /= 1.1;
	}
	else
	{
		if (keycode == KEY_PLUS && fdf->viewer.zoom < ZOOM_MAX)
			fdf->viewer.zoom *= 1.1;
		if (keycode == KEY_MINUS && fdf->viewer.zoom > ZOOM_MIN)
			fdf->viewer.zoom /= 1.1;
	}
}

void	fdf_on_number_down(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_0)
		fdf_set_view(fdf, 0);
	if (keycode == KEY_1)
		fdf_set_view(fdf, 1);
	if (keycode == KEY_2)
		fdf_set_view(fdf, 2);
	if (keycode == KEY_3)
		fdf_set_view(fdf, 3);
}

int	fdf_on_keydown(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf_exit(fdf);
	if (keycode == KEY_H)
		fdf->viewer.help = !fdf->viewer.help;
	if (keycode == KEY_P)
		fdf->viewer.perspective = !fdf->viewer.perspective;
	if (keycode == KEY_C)
		fdf->viewer.color = (fdf->viewer.color + 1) % 3;
	if (fdf->viewer.color == MAP_VALUES && !fdf->map.has_color)
		fdf->viewer.color = (fdf->viewer.color + 1) % 3;
	if (keycode == KEY_R)
		fdf->viewer.render = (fdf->viewer.render + 1) % 3;
	if (keycode == KEY_SPACE)
		fdf->ui.key_space = 1;
	if (keycode == KEY_Z)
		fdf->ui.key_z = 1;
	fdf_on_number_down(keycode, fdf);
	fdf_on_arrow_down(keycode, fdf);
	fdf_on_plus_minus_down(keycode, fdf);
	return (0);
}

int	fdf_on_keyup(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_SPACE)
		fdf->ui.key_space = 0;
	if (keycode == KEY_Z)
		fdf->ui.key_z = 0;
	return (0);
}
