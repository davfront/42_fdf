/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 17:10:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_pixel	fdf_proj_px(t_fdf *fdf, int x, int y)
{
	t_pixel		p;
	t_vertice	v;

	v = fdf->viewer.map_proj[x][y];
	p.x = v.x;
	p.y = v.y;
	p.color = v.color;
	return (p);
}

void	fdf_draw_xy_edge(t_fdf *fdf, int x, int y)
{
	t_pixel	p00;
	t_pixel	p10;
	t_pixel	p01;
	t_pixel	p11;

	if (x < fdf->map.size_x - 1 && y < fdf->map.size_y - 1)
	{
		p00 = fdf_proj_px(fdf, x, y);
		p10 = fdf_proj_px(fdf, x + 1, y);
		p01 = fdf_proj_px(fdf, x, y + 1);
		p11 = fdf_proj_px(fdf, x + 1, y + 1);
		fdf_draw_triangle(&fdf->img, p00, p10, p01);
		fdf_draw_triangle(&fdf->img, p10, p01, p11);
	}
}

void	fdf_draw_xy_lines(t_fdf *fdf, int x, int y)
{
	t_pixel	p00;
	t_pixel	p10;
	t_pixel	p01;
	t_pixel	p11;

	if (x < fdf->map.size_x - 1 && y < fdf->map.size_y - 1)
	{
		p00 = fdf_proj_px(fdf, x, y);
		p10 = fdf_proj_px(fdf, x + 1, y);
		p01 = fdf_proj_px(fdf, x, y + 1);
		p11 = fdf_proj_px(fdf, x + 1, y + 1);
		if (y == 0)
			fdf_draw_line(&fdf->img, p00, p10);
		if (x == 0)
			fdf_draw_line(&fdf->img, p00, p01);
		fdf_draw_line(&fdf->img, p10, p11);
		fdf_draw_line(&fdf->img, p01, p11);
	}
}

void	fdf_draw_map(t_fdf *fdf)
{
	int	x;
	int	y;
	int	x_rev;
	int	y_rev;

	fdf_update_proj(fdf);
	fdf_alloc_map_proj(fdf);
	fdf_get_map_proj(fdf);
	x_rev = (fdf->viewer.map_proj[1][0].z < fdf->viewer.map_proj[0][0].z);
	y_rev = (fdf->viewer.map_proj[0][1].z < fdf->viewer.map_proj[0][0].z);
	x = 0 + x_rev * (fdf->map.size_x - 1);
	while (x <= fdf->map.size_x - 1 && x >= 0)
	{
		y = 0 + y_rev * (fdf->map.size_y - 1);
		while (y <= fdf->map.size_y - 1 && y >= 0)
		{
			if (fdf->viewer.solid)
				fdf_draw_xy_edge(fdf, x, y);
			else
				fdf_draw_xy_lines(fdf, x, y);
			y += 1 - 2 * y_rev;
		}
		x += 1 - 2 * x_rev;
	}
	fdf_free_map_proj(fdf);
}
