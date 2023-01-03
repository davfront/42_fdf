/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:47:55 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/03 11:39:17 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_triangle_bottom(t_img *img, t_triangle t)
{
	float	len;
	t_pixel	p1;
	t_pixel	p2;
	int		i;

	if (t.top.y != t.mid.y || t.top.y == t.bot.y)
		return ;
	len = (float)t.top.y - (float)t.bot.y;
	i = 0;
	while (i <= len)
	{
		p1.x = t.bot.x + (int)(i * (t.top.x - t.bot.x) / len);
		p1.y = t.bot.y + i;
		p1.color = fdf_color_mix(t.bot.color, t.top.color, (float)i / len);
		p2.x = t.bot.x + (int)(i * (t.mid.x - t.bot.x) / len);
		p2.y = t.bot.y + i;
		p2.color = fdf_color_mix(t.bot.color, t.mid.color, (float)i / len);
		fdf_draw_line(img, p1, p2);
		i++;
	}
}

static void	fdf_draw_triangle_top(t_img *img, t_triangle t)
{
	float	len;
	t_pixel	p1;
	t_pixel	p2;
	int		i;

	if (t.bot.y != t.mid.y || t.bot.y == t.top.y)
		return ;
	len = (float)t.top.y - (float)t.bot.y;
	i = 0;
	while (i <= len)
	{
		p1.x = t.top.x - (int)(i * (t.top.x - t.bot.x) / len);
		p1.y = t.top.y - i;
		p1.color = fdf_color_mix(t.top.color, t.bot.color, (float)i / len);
		p2.x = t.top.x - (int)(i * (t.top.x - t.mid.x) / len);
		p2.y = t.top.y - i;
		p2.color = fdf_color_mix(t.top.color, t.mid.color, (float)i / len);
		fdf_draw_line(img, p1, p2);
		i++;
	}
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

static t_triangle	fdf_new_triangle(t_pixel p1, t_pixel p2, t_pixel p3)
{
	t_triangle	triangle;

	fdf_sort_pixels_by_y_asc(&p1, &p2, &p3);
	triangle.bot = p1;
	triangle.mid = p2;
	triangle.top = p3;
	return (triangle);
}

void	fdf_draw_triangle(t_img *img, t_pixel p1, t_pixel p2, t_pixel p3)
{
	t_triangle	t;
	t_pixel		p4;
	float		ratio;

	t = fdf_new_triangle(p1, p2, p3);
	if (t.bot.y == t.top.y)
		return ;
	if (t.mid.y == t.top.y)
		fdf_draw_triangle_bottom(img, t);
	else if (t.bot.y == t.mid.y)
		fdf_draw_triangle_top(img, t);
	else
	{
		ratio = (float)(t.mid.y - t.bot.y) / (float)(t.top.y - t.bot.y);
		p4.x = (int)(t.bot.x + ratio * (t.top.x - t.bot.x));
		p4.y = t.mid.y;
		p4.color = fdf_color_mix(t.bot.color, t.top.color, ratio);
		fdf_draw_triangle_bottom(img, fdf_new_triangle(t.bot, t.mid, p4));
		fdf_draw_triangle_top(img, fdf_new_triangle(t.mid, p4, t.top));
	}
}
