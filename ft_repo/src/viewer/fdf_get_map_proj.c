/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_proj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/14 19:23:58 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_get_point_color(t_fdf *fdf, int x, int y)
{
	int		color;
	int		map_color;
	int		map_z;
	float	r;

	color = WHITE;
	map_color = fdf->map.values[x][y].color;
	map_z = fdf->map.values[x][y].z;
	r = fabs((float)(map_z - fdf->map.z_min) / (float)fdf->map.dz);
	if (fdf->viewer.color == MAP_VALUES && map_color != -1)
		color = map_color;
	else if (fdf->viewer.color == Z_GRADIENT)
		color = fdf_color_mix(BLUE, RED, r);
	if (fdf->viewer.render == SOLID)
		color = fdf_color_mix(color, BLACK, (1 - r) * 0.2);
	return (color);
}

static void	fdf_project_point(t_fdf *fdf, int x, int y, t_vertice *p)
{
	float	v[4];

	v[0] = x;
	v[1] = y;
	v[2] = fdf->map.values[x][y].z;
	v[3] = 1.0;
	fdf_matrix_transform_point(v, fdf->viewer.proj);
	if (fdf->viewer.perspective)
	{
		p->x = WIN_WIDTH / 2
			+ (v[0] - WIN_WIDTH / 2) / (1 - v[2] / fdf->viewer.z_cam);
		p->y = WIN_HEIGHT / 2
			+ (v[1] - WIN_HEIGHT / 2) / (1 - v[2] / fdf->viewer.z_cam);
	}
	else
	{
		p->x = v[0];
		p->y = v[1];
	}
	p->z = v[2];
	p->color = fdf_get_point_color(fdf, x, y);
}

void	fdf_get_map_proj(t_fdf *fdf)
{
	int	x;
	int	y;

	x = 0;
	while (x < fdf->map.size_x)
	{
		y = 0;
		while (y < fdf->map.size_y)
		{
			fdf_project_point(fdf, x, y, &fdf->viewer.map_proj[x][y]);
			y++;
		}
		x++;
	}
}
