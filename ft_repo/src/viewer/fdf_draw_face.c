/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_face.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/16 20:47:31 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_get_face_pixels(t_fdf *fdf, t_pixel	(*p)[2][2], int x, int y)
{
	(*p)[0][0] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x][y]);
	(*p)[1][0] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x + 1][y]);
	(*p)[0][1] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x][y + 1]);
	(*p)[1][1] = fdf_vertice_to_pixel(fdf->viewer.map_proj[x + 1][y + 1]);
}

static void	fdf_draw_triangles(t_fdf *fdf, t_pixel (*p)[2][2], int x, int y)
{
	int		z1;
	int		z2;

	z1 = fdf->map.values[x][y].z + fdf->map.values[x + 1][y + 1].z;
	z2 = fdf->map.values[x + 1][y].z + fdf->map.values[x][y + 1].z;
	if (z1 < z2)
	{
		fdf_draw_triangle(fdf, (*p)[0][0], (*p)[1][0], (*p)[1][1]);
		fdf_draw_triangle(fdf, (*p)[0][0], (*p)[1][1], (*p)[0][1]);
	}
	else
	{
		fdf_draw_triangle(fdf, (*p)[0][0], (*p)[1][0], (*p)[0][1]);
		fdf_draw_triangle(fdf, (*p)[1][0], (*p)[1][1], (*p)[0][1]);
	}
}

static int	fdf_is_face_visible(t_fdf *fdf, int x, int y)
{
	t_vertice	v[2][2];

	if (x >= fdf->map.size_x - 1 || y >= fdf->map.size_y - 1)
		return (0);
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

void	fdf_draw_face(t_fdf *fdf, int x, int y)
{
	t_pixel	p[2][2];

	if (!fdf_is_face_visible(fdf, x, y))
		return ;
	if (fdf->viewer.render != WIREFRAME)
	{
		fdf_get_face_pixels(fdf, &p, x, y);
		if (fdf->viewer.render == WIREFRAME_NO_HIDDEN)
		{
			p[0][0].color = BLACK;
			p[1][0].color = BLACK;
			p[0][1].color = BLACK;
			p[1][1].color = BLACK;
			p[0][0].z -= 2;
			p[1][0].z -= 2;
			p[0][1].z -= 2;
			p[1][1].z -= 2;
		}
		fdf_draw_triangles(fdf, &p, x, y);
	}
	fdf_get_face_pixels(fdf, &p, x, y);
	fdf_draw_line(fdf, p[0][0], p[1][0]);
	fdf_draw_line(fdf, p[0][0], p[0][1]);
	fdf_draw_line(fdf, p[1][0], p[1][1]);
	fdf_draw_line(fdf, p[0][1], p[1][1]);
}
