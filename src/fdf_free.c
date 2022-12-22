/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 13:42:49 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_free(t_fdf *fdf)
{
	if (fdf->map.values)
	{
		while (fdf->map.size_x > 0)
		{
			if (fdf->map.values[fdf->map.size_x - 1])
				free(fdf->map.values[fdf->map.size_x - 1]);
			fdf->map.size_x--;
		}
		free(fdf->map.values);
	}
	fdf->map.values = NULL;
	fdf->map.size_x = 0;
	fdf->map.size_y = 0;
	return (0);
}
