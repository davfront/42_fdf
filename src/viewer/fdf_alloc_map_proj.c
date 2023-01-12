/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_alloc_map_proj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 17:26:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_alloc_map_proj(t_fdf *fdf)
{
	int	x;

	fdf->viewer.map_proj = ft_calloc(fdf->map.size_x, sizeof(t_vertice *));
	if (fdf->viewer.map_proj == NULL)
		fdf_error_exit(NULL);
	x = 0;
	while (x < fdf->map.size_x)
	{
		fdf->viewer.map_proj[x] = ft_calloc(fdf->map.size_y, sizeof(t_vertice));
		if (fdf->viewer.map_proj[x] == NULL)
		{
			fdf_free_all(fdf);
			fdf_error_exit(NULL);
		}
		x++;
	}
}
