/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/11 17:20:46 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_project_point(t_fdf *fdf, int x, int y, t_vertice *p)
{
	float	m[4][4];
	float	v[4];
	float	z_cam;
	float	r;



	z_cam = fmax(WIN_WIDTH, WIN_HEIGHT);
	v[0] = x;
	v[1] = y;
	v[2] = fdf->map.values[x][y].z;
	v[3] = 1.0;
	fdf_matrix_init(m);
	fdf_matrix_translate(m, -fdf->map.size_x / 2, -fdf->map.size_y / 2);
	fdf_matrix_scale(m, fdf->zoom, fdf->zoom, fdf->zoom * fdf->z_scale);
	fdf_matrix_multiply(m, fdf->mt);
	fdf_matrix_rotate_y(m, -(fdf->opt.mouse_x - fdf->opt.mouse_x0) * fdf->opt.mouse_right_btn * ROTATE_STEP_MOUSE);
	fdf_matrix_rotate_x(m, (fdf->opt.mouse_y - fdf->opt.mouse_y0) * fdf->opt.mouse_right_btn * ROTATE_STEP_MOUSE);
	fdf_matrix_translate(m, \
		fdf->cx + (fdf->opt.mouse_x - fdf->opt.mouse_x0) * fdf->opt.mouse_left_btn, \
		fdf->cy + (fdf->opt.mouse_y - fdf->opt.mouse_y0) * fdf->opt.mouse_left_btn);
	fdf_matrix_transform_point(v, m);
	if (fdf->opt.perspective)
	{
		p->x = WIN_WIDTH / 2 + (v[0] - WIN_WIDTH / 2) / (1 - v[2] / z_cam);
		p->y = WIN_HEIGHT / 2 + (v[1] - WIN_HEIGHT / 2) / (1 - v[2] / z_cam);
		p->z = v[2] - z_cam;
	}
	else
	{
		p->x = v[0];
		p->y = v[1];
		p->z = v[2];
	}
	if (fdf->map.has_color)
	{
		p->color = fdf->map.values[x][y].color;
		if (p->color == -1)
			p->color = COLOR_TXT;
	}
	else
	{
		r = fabs((float)(fdf->map.values[x][y].z - fdf->map.z_min) / (float)fdf->map.dz);
	p->color = fdf_color_mix(COLOR_BOTTOM, COLOR_TOP, r);
	}
}

void	fdf_project_map(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->map.size_x)
	{
		y = 0;
		while (y < fdf->map.size_y)
		{
			fdf_project_point(fdf, x, y, &fdf->proj[x][y]);
			y++;
		}
		x++;
	}
}

void	fdf_alloc_projection(t_fdf *fdf)
{
	int	x;

	fdf->proj = ft_calloc(fdf->map.size_x, sizeof(t_vertice *));
	if (fdf->proj == NULL)
		fdf_error_exit(NULL);
	x = 0;
	while (x < fdf->map.size_x)
	{
		fdf->proj[x] = ft_calloc(fdf->map.size_y, sizeof(t_vertice));
		if (fdf->proj[x] == NULL)
		{
			// TODO FREE
			fdf_error_exit(NULL);
		}
		x++;
	}
}

void	fdf_free_projection(t_fdf *fdf)
{
	int	x;

	x = 0;
	while (x < fdf->map.size_x)
	{
		ft_free(fdf->proj[x]);
		x++;
	}
	ft_free(fdf->proj);
}

static t_pixel	fdf_proj_px(t_fdf *fdf, int x, int y)
{
	t_pixel		p;
	t_vertice	v;

	v = fdf->proj[x][y];
	p.x = v.x;
	p.y = v.y;
	p.color = v.color;
	return (p);
}

void	fdf_draw_map(t_fdf *fdf)
{
	int	x;
	int	y;
	int	x_rev;
	int	y_rev;

	fdf_alloc_projection(fdf);
	fdf_project_map(fdf);
	x_rev = (fdf->proj[1][0].z < fdf->proj[0][0].z);
	y_rev = (fdf->proj[0][1].z < fdf->proj[0][0].z);
	x = 0 + x_rev * (fdf->map.size_x - 1);
	while (x <= fdf->map.size_x - 1 && x >= 0)
	{
		y = 0 + y_rev * (fdf->map.size_y - 1);
		while (y <= fdf->map.size_y - 1 && y >= 0)
		{
			if (fdf->opt.solid)
			{
				if (x < fdf->map.size_x - 1 && y < fdf->map.size_y - 1)
				{
					fdf_draw_triangle(&fdf->img, fdf_proj_px(fdf, x, y), fdf_proj_px(fdf, x + 1, y), fdf_proj_px(fdf, x, y + 1));
					fdf_draw_triangle(&fdf->img, fdf_proj_px(fdf, x + 1, y), fdf_proj_px(fdf, x, y + 1), fdf_proj_px(fdf, x + 1, y + 1));
				}
			}
			else
			{
				if (x < fdf->map.size_x - 1)
					fdf_draw_line(&fdf->img, fdf_proj_px(fdf, x, y), fdf_proj_px(fdf, x + 1, y));
				if (y < fdf->map.size_y - 1)
					fdf_draw_line(&fdf->img, fdf_proj_px(fdf, x, y), fdf_proj_px(fdf, x, y + 1));
			}
			y += 1 - 2 * y_rev;
		}
		x += 1 - 2 * x_rev;
	}
	fdf_free_projection(fdf);
}

int	fdf_render_frame(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, \
		&fdf->img.len, &fdf->img.endian);
	// fdf_set_bg(fdf);
	fdf_draw_map(fdf);
	// fdf_draw_help(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	return (0);
}
