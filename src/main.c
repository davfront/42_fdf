/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:55:19 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 15:25:19 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf_data;
	t_fdf	*fdf;

	fdf = &fdf_data;
	fdf_get_input(argc, argv, fdf);
	fdf_read_map(fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, fdf->title);
	fdf_hooks(fdf);
	mlx_loop_hook(fdf->mlx, fdf_render_frame, fdf);
	mlx_loop(fdf->mlx);
	return (EXIT_SUCCESS);
}
