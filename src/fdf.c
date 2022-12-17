/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/17 09:16:57 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char** argv)
{
	t_fdf	fdf;
	void	*mlx;
	void	*mlx_win;
	t_img	img;

	if (!fdf_get_input(argc, argv, &fdf))
		return (1);
	if (!fdf_read(&fdf))
		return (1);

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, fdf.filename);
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	fdf_draw_line(&img, fdf_new_pixel(20, 20, WHITE), fdf_new_pixel(200, 50, RED));
	fdf_draw_line(&img, fdf_new_pixel(200, 50, WHITE), fdf_new_pixel(200, 200, RED));
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	return (0);
}
