/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_edge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/13 15:42:10 by dapereir         ###   ########.fr       */
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

static void	fdf_get_edge_pixels(t_fdf *fdf, t_pixel	(*p)[2][2], int x, int y, \
	int force_bg_color)
{
	(*p)[0][0] = fdf_proj_px(fdf, x, y);
	(*p)[1][0] = fdf_proj_px(fdf, x + 1, y);
	(*p)[0][1] = fdf_proj_px(fdf, x, y + 1);
	(*p)[1][1] = fdf_proj_px(fdf, x + 1, y + 1);
	if (force_bg_color)
	{
		(*p)[0][0].color = COLOR_BG;
		(*p)[1][0].color = COLOR_BG;
		(*p)[0][1].color = COLOR_BG;
		(*p)[1][1].color = COLOR_BG;
	}
}

static void	fdf_draw_xy_solid(t_fdf *fdf, int x, int y, int force_bg_color)
{
	t_pixel	p[2][2];
	int		z1;
	int		z2;

	if (x < fdf->map.size_x - 1 && y < fdf->map.size_y - 1)
	{
		fdf_get_edge_pixels(fdf, &p, x, y, force_bg_color);
		z1 = fdf->map.values[x][y].z + fdf->map.values[x + 1][y + 1].z;
		z2 = fdf->map.values[x + 1][y].z + fdf->map.values[x][y + 1].z;
		if (z1 < z2 && fdf->viewer.z_rev)
		{
			fdf_draw_triangle(&fdf->img, p[0][0], p[1][0], p[1][1]);
			fdf_draw_triangle(&fdf->img, p[0][0], p[1][1], p[0][1]);
		}
		else
		{
			fdf_draw_triangle(&fdf->img, p[0][0], p[1][0], p[0][1]);
			fdf_draw_triangle(&fdf->img, p[1][0], p[1][1], p[0][1]);
		}
	}
}

static void	fdf_draw_xy_wireframe(t_fdf *fdf, int x, int y)
{
	t_pixel	p[2][2];

	if (x < fdf->map.size_x - 1 && y < fdf->map.size_y - 1)
	{
		fdf_get_edge_pixels(fdf, &p, x, y, 0);
		fdf_draw_line(&fdf->img, p[0][0], p[1][0]);
		fdf_draw_line(&fdf->img, p[0][0], p[0][1]);
		fdf_draw_line(&fdf->img, p[1][0], p[1][1]);
		fdf_draw_line(&fdf->img, p[0][1], p[1][1]);
	}
}

void	fdf_draw_edge(t_fdf *fdf, int x, int y)
{
	t_render	r;

	r = fdf->viewer.render;
	if (r == SOLID || r == WIREFRAME_NO_HIDDEN)
		fdf_draw_xy_solid(fdf, x, y, r == WIREFRAME_NO_HIDDEN);
	if (r == WIREFRAME || r == WIREFRAME_NO_HIDDEN)
		fdf_draw_xy_wireframe(fdf, x, y);
}
