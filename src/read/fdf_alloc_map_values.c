/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_alloc_map_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:33:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_alloc_map_values(t_fdf *fdf)
{
	int	i;

	fdf->map.values = ft_calloc(fdf->map.size_x, sizeof(int *));
	if (fdf->map.values == NULL)
		fdf_error_exit(NULL);
	i = 0;
	while (i < fdf->map.size_x)
	{
		fdf->map.values[i] = ft_calloc(fdf->map.size_y, sizeof(int));
		if (fdf->map.values[i] == NULL)
		{
			fdf_reset(fdf);
			fdf_error_exit(NULL);
		}
		i++;
	}
}
