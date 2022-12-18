/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/18 01:48:27 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_map_to_pixel(t_fdf *fdf, int x, int y, t_pixel *p)
{
	t_vertice	v;
	t_vertice	v2;
	float		x_scale;
	float		y_scale;
	float		h_scale;
	int			x0;
	int			y0;

	x_scale = (WIN_WIDTH * 0.8 / (fdf->map.size_x - 1));
	y_scale = (WIN_HEIGHT * 0.8 / (fdf->map.size_y - 1));
	h_scale = fmin(x_scale, y_scale);
	x0 = (WIN_WIDTH - (fdf->map.size_x - 1) * h_scale) / 2;
	y0 = (WIN_HEIGHT - (fdf->map.size_y - 1) * h_scale) / 2;

	v.x = x * h_scale + x0;
	v.y = y * h_scale + y0;
	v.z = fdf->map.values[x][y];

	// rotate X by 90deg
	v2.x = v.x;
	v2.y = -v.z;
	v2.z = v.y;
	v = v2;

	// rotate Y by 45deg
	v2.x = cos(PI / 4) * v.x - sin(PI / 4) * v.z;
	v2.y = v.y;
	v2.z = sin(PI / 4) * v.x + cos(PI / 4) * v.z;
	v = v2;

	// rotate X by 35deg
	v2.x = v.x;
	v2.y = cos(PI / 5) * v.y + sin(PI / 5) * v.z;
	v2.z = -sin(PI / 5) * v.y + cos(PI / 5) * v.z;
	v = v2;

	// translate
	v.x += WIN_WIDTH * 0.4;

	p->color = fdf_color_mix(COLOR_BOTTOM, COLOR_TOP, fdf->map.values[x][y] / 10);
	p->x = v.x;
	p->y = v.y;
}

void	fdf_draw_x_edge(t_fdf *fdf, int x, int y)
{
	t_pixel	p1;
	t_pixel	p2;

	if (x < 0 || x > fdf->map.size_x - 2)
		return ;
	fdf_map_to_pixel(fdf, x, y, &p1);
	fdf_map_to_pixel(fdf, x + 1, y, &p2);
	fdf_draw_line(&fdf->img, p1, p2);
}

void	fdf_draw_y_edge(t_fdf *fdf, int x, int y)
{
	t_pixel	p1;
	t_pixel	p2;

	if (y < 0 || y > fdf->map.size_y - 2)
		return ;
	fdf_map_to_pixel(fdf, x, y, &p1);
	fdf_map_to_pixel(fdf, x, y + 1, &p2);
	fdf_draw_line(&fdf->img, p1, p2);
}

void	fdf_draw_frame(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->map.size_x)
	{
		y = 0;
		while (y < fdf->map.size_y)
		{
			fdf_draw_x_edge(fdf, x, y);
			fdf_draw_y_edge(fdf, x, y);
			y++;
		}
		x++;
	}
}

void	fdf_render_frame(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, \
		&fdf->img.len, &fdf->img.endian);
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
