/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:34 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:21:52 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_set_bg(t_fdf *fdf)
{
	int		i;
	int		j;
	t_pixel	p;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			p.x = i;
			p.y = j;
			p.color = COLOR_BG;
			fdf_draw_pixel(&fdf->img, p);
			j++;
		}
		i++;
	}
}
