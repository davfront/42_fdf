/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/03 10:57:34 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_project_pixel(t_fdf *fdf, int x, int y, t_pixel *p)
{
	float	m[4][4];
	float	v[4];
	float	z_cam;
	float	r;

	z_cam = fmax(WIN_WIDTH, WIN_HEIGHT);
	v[0] = x;
	v[1] = y;
	v[2] = fdf->map.values[x][y] / 10;
	v[3] = 1.0;
	fdf_matrix_init(m);
	fdf_matrix_multiply(m, fdf->mt);
	fdf_matrix_transform_point(v, m);
	if (fdf->opt.perspective)
	{
		p->x = WIN_WIDTH / 2 + (v[0] - WIN_WIDTH / 2) / (1 - v[2] / z_cam);
		p->y = WIN_HEIGHT / 2 + (v[1] - WIN_HEIGHT / 2) / (1 - v[2] / z_cam);
	}
	else
	{
		p->x = v[0];
		p->y = v[1];
	}
	r = 0;
	if (fdf->map.z_max != fdf->map.z_min)
	r = fabs((float)(fdf->map.values[x][y] - fdf->map.z_min) / (float)(fdf->map.z_max - fdf->map.z_min));
	p->color = fdf_color_mix(COLOR_BOTTOM, COLOR_TOP, r);
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
			fdf_project_pixel(fdf, x, y, &fdf->proj[x][y]);
			y++;
		}
		x++;
	}
}

void	fdf_alloc_projection(t_fdf *fdf)
{
	int	x;

	fdf->proj = ft_calloc(fdf->map.size_x, sizeof(t_pixel *));
	if (fdf->proj == NULL)
		fdf_error_exit(NULL);
	x = 0;
	while (x < fdf->map.size_x)
	{
		fdf->proj[x] = ft_calloc(fdf->map.size_y, sizeof(t_pixel));
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

void	fdf_draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf_alloc_projection(fdf);
	fdf_project_map(fdf);
	x = 0;
	while (x < fdf->map.size_x)
	{
		y = 0;
		while (y < fdf->map.size_y)
		{
			if (fdf->opt.solid)
			{
				if (x < fdf->map.size_x - 1 && y < fdf->map.size_y - 1)
				{
					fdf_draw_triangle(&fdf->img, fdf->proj[x][y], fdf->proj[x + 1][y], fdf->proj[x][y + 1]);
					fdf_draw_triangle(&fdf->img, fdf->proj[x + 1][y], fdf->proj[x][y + 1], fdf->proj[x + 1][y + 1]);
				}
			}
			else
			{
				if (x < fdf->map.size_x - 1)
					fdf_draw_line(&fdf->img, fdf->proj[x][y], fdf->proj[x + 1][y]);
				if (y < fdf->map.size_y - 1)
					fdf_draw_line(&fdf->img, fdf->proj[x][y], fdf->proj[x][y + 1]);
			}
			y++;
		}
		x++;
	}
	fdf_free_projection(fdf);
}

void	fdf_draw_text(t_fdf *fdf, int line, char *text)
{
	mlx_string_put(fdf->mlx, fdf->win, 20, 20 + 20 * line, COLOR_TXT, text);
}

void	fdf_draw_help(t_fdf *fdf)
{
	int line;

	line = 1;
	fdf_draw_text(fdf, line++, "[H] Help");
	if (!fdf->opt.help)
		return ;
	line++;
	fdf_draw_text(fdf, line++, "[0] Isometric view");
	fdf_draw_text(fdf, line++, "[1] Z-axis view");
	fdf_draw_text(fdf, line++, "[2] X-axis view");
	fdf_draw_text(fdf, line++, "[3] Y-axis view");
	line++;
	fdf_draw_text(fdf, line++, "[P] Projection mode (Orthogonal <-> Perspective)");
	fdf_draw_text(fdf, line++, "[R] Rendering mode (Wireframe <-> Solid)");
	line++;
	fdf_draw_text(fdf, line++, "[+] Zoom in");
	fdf_draw_text(fdf, line++, "[-] Zoom out");
	line++;
	fdf_draw_text(fdf, line++, ft_itoa(fdf->opt.mouse.x));
	fdf_draw_text(fdf, line++, ft_itoa(fdf->opt.mouse.y));
}

int	fdf_render_frame(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, \
		&fdf->img.len, &fdf->img.endian);
	// fdf_set_bg(fdf);
	fdf_draw_map(fdf);
	fdf_draw_help(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	return (0);
}
