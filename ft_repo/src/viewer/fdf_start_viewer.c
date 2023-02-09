/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_viewer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:03:41 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/18 10:24:17 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_start_viewer(t_fdf *fdf)
{
	fdf_init_ui(fdf);
	fdf_init_viewer(fdf);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		fdf_free_all(fdf);
		fdf_error_exit("Minilibx initialization failed");
	}
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, fdf->title);
	ft_printf("[%s] File opened - For Help, press [H] in the viewer\n", \
		fdf->title);
	fdf_hooks(fdf);
	mlx_loop_hook(fdf->mlx, fdf_render_frame, fdf);
	mlx_loop(fdf->mlx);
}
