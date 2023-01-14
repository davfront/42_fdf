/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_edge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/14 22:38:49 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_get_edge_pixels(t_fdf *fdf, t_pixel	(*p)[2][2], int x, int y, \
	int force_bg_color)
{
	(*p)[0][0] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x][y]);
	(*p)[1][0] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x + 1][y]);
	(*p)[0][1] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x][y + 1]);
	(*p)[1][1] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x + 1][y + 1]);
	if (force_bg_color)
	{
		(*p)[0][0].color = BLACK;
		(*p)[1][0].color = BLACK;
		(*p)[0][1].color = BLACK;
		(*p)[1][1].color = BLACK;
	}
	else if (fdf->viewer.help)
	{
		(*p)[0][0].color = fdf_color_mix((*p)[0][0].color, BLACK, 0.75);
		(*p)[1][0].color = fdf_color_mix((*p)[1][0].color, BLACK, 0.75);
		(*p)[0][1].color = fdf_color_mix((*p)[0][1].color, BLACK, 0.75);
		(*p)[1][1].color = fdf_color_mix((*p)[1][1].color, BLACK, 0.75);
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

static int	fdf_is_edge_visible(t_fdf *fdf, int x, int y)
{
	t_vertice	v[2][2];

	v[0][0] = fdf->viewer.map_proj[x][y];
	v[1][0] = fdf->viewer.map_proj[x + 1][y];
	v[0][1] = fdf->viewer.map_proj[x][y + 1];
	v[1][1] = fdf->viewer.map_proj[x + 1][y + 1];
	if (v[0][0].x < 0 && v[1][0].x < 0 && v[0][1].x < 0 && v[1][1].x < 0)
		return (0);
	if (v[0][0].x >= WIN_WIDTH && v[1][0].x >= WIN_WIDTH
		&& v[0][1].x >= WIN_WIDTH && v[1][1].x >= WIN_WIDTH)
		return (0);
	if (v[0][0].y < 0 && v[1][0].y < 0 && v[0][1].y < 0 && v[1][1].y < 0)
		return (0);
	if (v[0][0].y >= WIN_HEIGHT && v[1][0].y >= WIN_HEIGHT
		&& v[0][1].y >= WIN_HEIGHT && v[1][1].y >= WIN_HEIGHT)
		return (0);
	if (fdf->viewer.perspective && (v[0][0].z >= fdf->viewer.z_cam
		|| v[1][0].z >= fdf->viewer.z_cam || v[0][1].z >= fdf->viewer.z_cam
		|| v[1][1].z >= fdf->viewer.z_cam))
		return (0);
	return (1);
}

void	fdf_draw_edge(t_fdf *fdf, int x, int y)
{
	t_render	r;

	if (!fdf_is_edge_visible(fdf, x, y))
		return ;
	r = fdf->viewer.render;
	if (r == SOLID || r == WIREFRAME_NO_HIDDEN)
		fdf_draw_xy_solid(fdf, x, y, r == WIREFRAME_NO_HIDDEN);
	if (r == WIREFRAME || r == WIREFRAME_NO_HIDDEN)
		fdf_draw_xy_wireframe(fdf, x, y);
}
