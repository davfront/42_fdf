/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/17 14:25:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_frame(t_fdf *fdf)
{
	fdf_draw_line(&fdf->img, fdf_new_pixel(20, 20, WHITE), fdf_new_pixel(200, 50, RED));
	fdf_draw_line(&fdf->img, fdf_new_pixel(200, 50, WHITE), fdf_new_pixel(200, 200, RED));
}

void	fdf_render_frame(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, &fdf->img.len, &fdf->img.endian);
	fdf_draw_frame(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf_data;
	t_fdf	*fdf;

    fdf = &fdf_data;
	if (!fdf_get_input(argc, argv, fdf))
		return (1);
	if (!fdf_read(fdf))
		return (1);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, fdf->title);
    fdf_render_frame(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
