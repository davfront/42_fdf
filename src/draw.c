/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:34 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/14 16:35:35 by dapereir         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// #define ABS(X) (((X) < 0) ? (-(X)) : (X))

static float    fdf_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	fdf_draw_pixel(t_data *data, t_point p, int color)
{
	char	*dst;

	dst = data->addr;
	dst += p.y * data->line_length;
	dst += p.x * (data->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

void	fdf_draw_line(t_data *data, t_point p1, t_point p2, int color1, int color2)
{
	float	len;
	float	len_x;
	float	len_y;
	float	delta_x;
	float	delta_y;
	int		i;
	int		color;
	t_point	p;

	if (p1.x == p2.x && p1.y == p2.y)
	{
		fdf_draw_pixel(data, p1, WHITE);
		return;
	}
	len_x = fdf_abs((float)p2.x - (float)p1.x);
	len_y = fdf_abs((float)p2.y - (float)p1.y);
	len = len_x;
	if (len < len_y)
		len = len_y;
	delta_x = ((float)p2.x - (float)p1.x) / len;
	delta_y = ((float)p2.y - (float)p1.y) / len;
	i = 0;
	while (i < len)
	{
		p.x = p1.x + (int)(i * delta_x);
		p.y = p1.y + (int)(i * delta_y);
		color = fdf_color_mix(color1, color2, (float)i / len);
		fdf_draw_pixel(data, p, color);
		i++;
	}
}
