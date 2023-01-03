/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:47:55 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/03 10:54:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_triangle_bottom(t_img *img, t_pixel bottom, t_pixel top1, t_pixel top2)
{
	float	len;
	t_pixel	p1;
	t_pixel	p2;
	int		i;

	if (top1.y != top2.y || top1.y == bottom.y)
		return ;
	len = (float)top1.y - (float)bottom.y;
	i = 0;
	while (i <= len)
	{
		p1.x = bottom.x + (int)(i * (top1.x - bottom.x) / len);
		p1.y = bottom.y + i;
		p1.color = fdf_color_mix(bottom.color, top1.color, (float)i / len);
		p2.x = bottom.x + (int)(i * (top2.x - bottom.x) / len);
		p2.y = bottom.y + i;
		p2.color = fdf_color_mix(bottom.color, top2.color, (float)i / len);
		fdf_draw_line(img, p1, p2);
		i++;
	}
}

static void	fdf_draw_triangle_top(t_img *img, t_pixel bottom1, t_pixel bottom2, t_pixel top)
{
	float	len;
	t_pixel	p1;
	t_pixel	p2;
	int		i;

	if (bottom1.y != bottom2.y || bottom1.y == top.y)
		return ;
	len = (float)top.y - (float)bottom1.y;
	i = 0;
	while (i <= len)
	{
		p1.x = top.x - (int)(i * (top.x - bottom1.x) / len);
		p1.y = top.y - i;
		p1.color = fdf_color_mix(top.color, bottom1.color, (float)i / len);
		p2.x = top.x - (int)(i * (top.x - bottom2.x) / len);
		p2.y = top.y - i;
		p2.color = fdf_color_mix(top.color, bottom2.color, (float)i / len);
		fdf_draw_line(img, p1, p2);
		i++;
	}
}

static void	fdf_swap_pixels(t_pixel *p1, t_pixel *p2)
{
	t_pixel	tmp;

	tmp = *p2;
	*p2 = *p1;
	*p1 = tmp;
}

static void	fdf_sort_pixels_by_y_asc(t_pixel *p1, t_pixel *p2, t_pixel *p3)
{
	if (p1->y > p2->y)
		fdf_swap_pixels(p1, p2);
	if (p1->y > p3->y)
		fdf_swap_pixels(p1, p3);
	if (p2->y > p3->y)
		fdf_swap_pixels(p2, p3);
}

void	fdf_draw_triangle(t_img *img, t_pixel p1, t_pixel p2, t_pixel p3)
{
	t_pixel	p4;
	float	ratio;

	fdf_sort_pixels_by_y_asc(&p1, &p2, &p3);
	if (p1.y == p3.y)
		return ;
	if (p2.y == p3.y)
		fdf_draw_triangle_bottom(img, p1, p2, p3);
	else if (p1.y == p2.y)
		fdf_draw_triangle_top(img, p1, p2, p3);
	else
	{
		ratio = (float)(p2.y - p1.y) / (float)(p3.y - p1.y);
		p4.x = (int)(p1.x + ratio * (p3.x - p1.x));
		p4.y = p2.y;
		p4.color = fdf_color_mix(p1.color, p3.color, ratio);
		fdf_draw_triangle_bottom(img, p1, p2, p4);
		fdf_draw_triangle_top(img, p2, p4, p3);
	}
}
