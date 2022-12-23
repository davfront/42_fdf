/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 21:37:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_mt(t_fdf *fdf)
{
	fdf_matrix_init(fdf->mt);
	
	// translate center of map to origin
	fdf_matrix_translate(fdf->mt, -fdf->map.size_x / 2, -fdf->map.size_y / 2);

	// scale
	fdf_matrix_scale(fdf->mt, fdf->zoom, fdf->zoom, fdf->z_scale * fdf->zoom);

	// rotate X by 90deg
	fdf_matrix_rotate_x(fdf->mt, - PI / 2);

	// rotate Y by 45deg
	fdf_matrix_rotate_y(fdf->mt, PI / 4);

	// rotate X by 35deg
	fdf_matrix_rotate_x(fdf->mt, PI / 5);

	// translate to center of screen
	fdf_matrix_translate(fdf->mt, WIN_WIDTH / 2, WIN_HEIGHT / 2);

}

static void	fdf_map_to_pixel(t_fdf *fdf, int x, int y, t_pixel *p)
{
	float	v[4] = {x, y, fdf->map.values[x][y] / 10, 1.0};
	float	m[4][4];
	// float	z_cam = 800.0;

	fdf_matrix_init(m);
	fdf_matrix_multiply(m, fdf->mt);
	fdf_matrix_transform_point(v, m);
	
	p->x = v[0];
	p->y = v[1];
	// p->x = WIN_WIDTH / 2 + (v[0] - WIN_WIDTH / 2) / (1 - v[2] / z_cam);
	// p->y = WIN_HEIGHT / 2 + (v[1] - WIN_HEIGHT / 2) / (1 - v[2] / z_cam);
	p->color = fdf_color_mix(COLOR_BOTTOM, COLOR_TOP, \
		fdf->map.values[x][y] / 10);
}

static void	fdf_draw_x_edge(t_fdf *fdf, int x, int y)
{
	t_pixel	p1;
	t_pixel	p2;

	if (x < 0 || x > fdf->map.size_x - 2)
		return ;
	fdf_map_to_pixel(fdf, x, y, &p1);
	fdf_map_to_pixel(fdf, x + 1, y, &p2);
	fdf_draw_line(&fdf->img, p1, p2);
}

static void	fdf_draw_y_edge(t_fdf *fdf, int x, int y)
{
	t_pixel	p1;
	t_pixel	p2;

	if (y < 0 || y > fdf->map.size_y - 2)
		return ;
	fdf_map_to_pixel(fdf, x, y, &p1);
	fdf_map_to_pixel(fdf, x, y + 1, &p2);
	fdf_draw_line(&fdf->img, p1, p2);
}

static void	fdf_draw_frame(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf_set_bg(fdf);
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

int	fdf_render_frame(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, \
		&fdf->img.len, &fdf->img.endian);
	fdf_draw_frame(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	return (0);
}
