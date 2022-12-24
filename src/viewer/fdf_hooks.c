/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/24 09:41:39 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_on_keypress(int keycode, t_fdf *fdf)
{
	float	a;
	float	cx;
	float	cy;

	a = PI / 50;
	cx = WIN_WIDTH / 2;
	cy = WIN_HEIGHT / 2;
	if (keycode == KEY_ESC)
		fdf_exit(fdf);
	if (keycode == KEY_0)
		fdf_init_mt(fdf, 0);
	if (keycode == KEY_1)
		fdf_init_mt(fdf, 1);
	if (keycode == KEY_2)
		fdf_init_mt(fdf, 2);
	if (keycode == KEY_3)
		fdf_init_mt(fdf, 3);
	if (keycode == KEY_P)
		fdf->opt.perspective = !fdf->opt.perspective;
	if (keycode == KEY_LEFT)
		fdf_matrix_rotate_y_at(fdf->mt, a, cx, cy);
	if (keycode == KEY_RIGHT)
		fdf_matrix_rotate_y_at(fdf->mt, -a, cx, cy);
	if (keycode == KEY_UP)
		fdf_matrix_rotate_x_at(fdf->mt, -a, cx, cy);
	if (keycode == KEY_DOWN)
		fdf_matrix_rotate_x_at(fdf->mt, a, cx, cy);
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, fdf_on_keypress, fdf);
	mlx_hook(fdf->win, 17, 1L << 0, fdf_exit, fdf);
}
