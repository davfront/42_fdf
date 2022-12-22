/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 13:46:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_on_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf_exit(fdf);
	if (keycode == KEY_LEFT)
		fdf->ry -= 0.1;
	if (keycode == KEY_RIGHT)
		fdf->ry += 0.1;
	if (keycode == KEY_UP)
		fdf->rx -= 0.1;
	if (keycode == KEY_DOWN)
		fdf->rx += 0.1;
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, fdf_on_keypress, fdf);
	mlx_hook(fdf->win, 17, 1L << 0, fdf_exit, fdf);
}
