/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/16 10:53:16 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf_init_z_buffer(fdf);
	fdf_update_proj(fdf);
	fdf_alloc_map_proj(fdf);
	fdf_get_map_proj(fdf);
	x = 0;
	while (x <= fdf->map.size_x - 2)
	{
		y = 0;
		while (y <= fdf->map.size_y - 2)
		{
			fdf_draw_face(fdf, x, y);
			y++;
		}
		x++;
	}
	fdf_free_map_proj(fdf);
}
