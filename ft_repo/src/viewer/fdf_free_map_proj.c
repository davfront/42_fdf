/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free_map_proj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 16:59:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_free_map_proj(t_fdf *fdf)
{
	int	x;

	if (fdf->viewer.map_proj)
	{
		x = 0;
		while (x < fdf->map.size_x)
		{
			ft_free((void **)&fdf->viewer.map_proj[x]);
			x++;
		}
	}
	ft_free((void **)&fdf->viewer.map_proj);
}
