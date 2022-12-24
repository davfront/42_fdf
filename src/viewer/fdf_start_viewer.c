/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_viewer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:03:41 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/24 08:51:43 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_start_viewer(t_fdf *fdf)
{
	fdf_init_viewer(fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, fdf->title);
	fdf_hooks(fdf);
	mlx_loop_hook(fdf->mlx, fdf_render_frame, fdf);
	mlx_loop(fdf->mlx);
}
