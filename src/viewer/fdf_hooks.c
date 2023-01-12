/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 15:09:15 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 17, 1L << 0, fdf_exit, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, fdf_on_keydown, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, fdf_on_keyup, fdf);
	mlx_hook(fdf->win, 4, 1L << 2, fdf_on_mouse_down, fdf);
	mlx_hook(fdf->win, 5, 1L << 3, fdf_on_mouse_up, fdf);
	mlx_hook(fdf->win, 6, 1L << 6, fdf_on_mouse_move, fdf);
}
