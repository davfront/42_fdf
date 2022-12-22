/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 15:33:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_reset(t_fdf *fdf)
{
	if (fdf->map.values)
	{
		while (fdf->map.size_x > 0)
		{
			ft_free(fdf->map.values[fdf->map.size_x - 1]);
			fdf->map.size_x--;
		}
		ft_free(fdf->map.values);
	}
	fdf->map.size_y = 0;
	return (0);
}
