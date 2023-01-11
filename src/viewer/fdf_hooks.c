/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/11 15:54:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_on_keydown(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf_exit(fdf);
	if (keycode == KEY_H)
		fdf->opt.help = !fdf->opt.help;
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
	if (keycode == KEY_R)
		fdf->opt.solid = !fdf->opt.solid;
	if (fdf->opt.key_space)
	{
		if (keycode == KEY_LEFT)
			fdf->cx += -TRANSLATE_STEP;
		if (keycode == KEY_RIGHT)
			fdf->cx += TRANSLATE_STEP;
		if (keycode == KEY_UP)
			fdf->cy += -TRANSLATE_STEP;
		if (keycode == KEY_DOWN)
			fdf->cy += TRANSLATE_STEP;
	}
	else
	{
		if (keycode == KEY_LEFT)
			fdf_matrix_rotate_y(fdf->mt, ROTATE_STEP);
		if (keycode == KEY_RIGHT)
			fdf_matrix_rotate_y(fdf->mt, -ROTATE_STEP);
		if (keycode == KEY_UP)
			fdf_matrix_rotate_x(fdf->mt, -ROTATE_STEP);
		if (keycode == KEY_DOWN)
			fdf_matrix_rotate_x(fdf->mt, ROTATE_STEP);
	}
	if (fdf->opt.key_z)
	{
		if (keycode == KEY_PLUS)
			fdf->z_scale *= SCALE_STEP;
		if (keycode == KEY_MINUS)
			fdf->z_scale /= SCALE_STEP;
	}
	else
	{
		if (keycode == KEY_PLUS)
			fdf->zoom *= SCALE_STEP;
		if (keycode == KEY_MINUS)
			fdf->zoom /= SCALE_STEP;
	}
	if (keycode == KEY_SPACE)
		fdf->opt.key_space = 1;
	if (keycode == KEY_Z)
		fdf->opt.key_z = 1;
	return (0);
}

static int	fdf_on_keyup(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_SPACE)
		fdf->opt.key_space = 0;
	if (keycode == KEY_Z)
		fdf->opt.key_z = 0;
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 17, 1L << 0, fdf_exit, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, fdf_on_keydown, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, fdf_on_keyup, fdf);
}
