/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/11 17:20:54 by dapereir         ###   ########.fr       */
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

static int	fdf_on_mouse_down(int button, int x, int y, t_fdf *fdf)
{
	if (button == MOUSE_LEFT)
		fdf->opt.mouse_left_btn = 1;
	if (button == MOUSE_RIGHT)
		fdf->opt.mouse_right_btn = 1;
	fdf->opt.mouse_x0 = x;
	fdf->opt.mouse_y0 = y;
	fdf->opt.mouse_x = x;
	fdf->opt.mouse_y = y;
	return (0);
}

static int	fdf_on_mouse_up(int button, int x, int y, t_fdf *fdf)
{
	if (button == MOUSE_LEFT)
	{
		fdf->cx += x - fdf->opt.mouse_x0;
		fdf->cy += y - fdf->opt.mouse_y0;
		fdf->opt.mouse_left_btn = 0;
	}
	if (button == MOUSE_RIGHT)
	{
		fdf_matrix_rotate_y(fdf->mt, -(x - fdf->opt.mouse_x0) * ROTATE_STEP_MOUSE);
		fdf_matrix_rotate_x(fdf->mt, (y - fdf->opt.mouse_y0) * ROTATE_STEP_MOUSE);
		fdf->opt.mouse_right_btn = 0;
	}
	fdf->opt.mouse_x0 = 0;
	fdf->opt.mouse_y0 = 0;
	fdf->opt.mouse_x = 0;
	fdf->opt.mouse_y = 0;
	return (0);
}

static int	fdf_on_mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->opt.mouse_x = x;
	fdf->opt.mouse_y = y;
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 17, 1L << 0, fdf_exit, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, fdf_on_keydown, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, fdf_on_keyup, fdf);
	mlx_hook(fdf->win, 4, 1L<<6, fdf_on_mouse_down, fdf);
	mlx_hook(fdf->win, 5, 1L<<6, fdf_on_mouse_up, fdf);
	mlx_hook(fdf->win, 6, 1L<<6, fdf_on_mouse_move, fdf);
}
