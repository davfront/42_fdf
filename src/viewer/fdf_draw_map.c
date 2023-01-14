/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/13 17:00:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_get_map_proj_directions(t_fdf *fdf)
{
	float	v[4];
	float	v_x[4];
	float	v_y[4];
	float	v_z[4];

	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 1.0;
	ft_memcpy(v_x, v, sizeof(v));
	v_x[0] = 1000.0;
	fdf_matrix_transform_point(v_x, fdf->viewer.proj);
	ft_memcpy(v_y, v, sizeof(v));
	v_y[1] = 1000.0;
	fdf_matrix_transform_point(v_y, fdf->viewer.proj);
	ft_memcpy(v_z, v, sizeof(v));
	v_z[2] = 1000.0;
	fdf_matrix_transform_point(v_z, fdf->viewer.proj);
	fdf->viewer.x_rev = (v_x[2] < 0);
	fdf->viewer.y_rev = (v_y[2] < 0);
	fdf->viewer.z_rev = (v_z[2] > 0);
	fdf->viewer.x_loop_first = fabs(v_x[2]) > fabs(v_y[2]);
}

static void	fdf_draw_edges_xy(t_fdf *fdf)
{
	int	x;
	int	y;
	int	x_rev;
	int	y_rev;

	x_rev = fdf->viewer.x_rev;
	y_rev = fdf->viewer.y_rev;
	x = 0 + x_rev * (fdf->map.size_x - 2);
	while (x <= fdf->map.size_x - 2 && x >= 0)
	{
		y = 0 + y_rev * (fdf->map.size_y - 2);
		while (y <= fdf->map.size_y - 2 && y >= 0)
		{
			fdf_draw_edge(fdf, x, y);
			y += 1 - 2 * y_rev;
		}
		x += 1 - 2 * x_rev;
	}
}

static void	fdf_draw_edges_yx(t_fdf *fdf)
{
	int	x;
	int	y;
	int	x_rev;
	int	y_rev;

	x_rev = fdf->viewer.x_rev;
	y_rev = fdf->viewer.y_rev;
	y = 0 + y_rev * (fdf->map.size_y - 2);
	while (y <= fdf->map.size_y - 2 && y >= 0)
	{
		x = 0 + x_rev * (fdf->map.size_x - 2);
		while (x <= fdf->map.size_x - 2 && x >= 0)
		{
			fdf_draw_edge(fdf, x, y);
			x += 1 - 2 * x_rev;
		}
		y += 1 - 2 * y_rev;
	}
}

void	fdf_draw_map(t_fdf *fdf)
{
	fdf_update_proj(fdf);
	fdf_alloc_map_proj(fdf);
	fdf_get_map_proj(fdf);
	fdf_get_map_proj_directions(fdf);
	if (fdf->viewer.x_loop_first)
		fdf_draw_edges_xy(fdf);
	else
		fdf_draw_edges_yx(fdf);
	fdf_free_map_proj(fdf);
}
