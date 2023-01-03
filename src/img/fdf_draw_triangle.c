/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:47:55 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/03 15:04:25 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_triangle_pixel(t_img *img, t_pixel t[3], t_pixel p)
{
	float	w1;
	float	w2;
	float	w3;

	w1 = (float)((p.y - t[1].y) * (t[2].x - t[1].x) \
			- (p.x - t[1].x) * (t[2].y - t[1].y)) \
		/ ((t[0].y - t[1].y) * (t[2].x - t[1].x) \
			- (t[0].x - t[1].x) * (t[2].y - t[1].y));
	w2 = (float)((p.y - t[0].y) * (t[2].x - t[0].x) \
			- (p.x - t[0].x) * (t[2].y - t[0].y)) \
		/ ((t[1].y - t[0].y) * (t[2].x - t[0].x) \
			- (t[1].x - t[0].x) * (t[2].y - t[0].y));
	w3 = 1.0 - w1 - w2;
	if (w1 >= 0 && w2 >= 0 && w3 >= 0)
	{
		if (w1 + w2 == 0)
			p.color = t[2].color;
		else
		{
			p.color = fdf_color_mix(t[0].color, t[1].color, w2 / (w1 + w2));
			p.color = fdf_color_mix(p.color, t[2].color, w3);
		}
		fdf_draw_pixel(img, p);
	}
}

void	fdf_draw_triangle(t_img *img, t_pixel p1, t_pixel p2, t_pixel p3)
{
	t_pixel	min;
	t_pixel	max;
	t_pixel	t[3];
	t_pixel	p;

	min.x = fmin(p1.x, fmin(p2.x, p3.x));
	max.x = fmax(p1.x, fmax(p2.x, p3.x));
	min.y = fmin(p1.y, fmin(p2.y, p3.y));
	max.y = fmax(p1.y, fmax(p2.y, p3.y));
	p.x = min.x;
	while (p.x <= max.x)
	{
		p.y = min.y;
		while (p.y <= max.y)
		{
			t[0] = p1;
			t[1] = p2;
			t[2] = p3;
			fdf_draw_triangle_pixel(img, t, p);
			p.y++;
		}
		p.x++;
	}
}
