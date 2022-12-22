/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:34 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:20:50 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_line(t_img *img, t_pixel p1, t_pixel p2)
{
	float	len;
	float	delta_x;
	float	delta_y;
	int		i;
	t_pixel	p;

	if (p1.x == p2.x && p1.y == p2.y)
	{
		fdf_draw_pixel(img, p1);
		return ;
	}
	len = fabs((float)p2.x - (float)p1.x);
	len = fmax(len, fabs((float)p2.y - (float)p1.y));
	delta_x = ((float)p2.x - (float)p1.x) / len;
	delta_y = ((float)p2.y - (float)p1.y) / len;
	i = 0;
	while (i < len)
	{
		p.x = p1.x + (int)(i * delta_x);
		p.y = p1.y + (int)(i * delta_y);
		p.color = fdf_color_mix(p1.color, p2.color, (float)i / len);
		fdf_draw_pixel(img, p);
		i++;
	}
}
