/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:26 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/14 16:35:28 by dapereir         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_trgb	fdf_color_trgb(int color)
{
	t_trgb	c;

	c.b = color % 256;
	c.g = (color / 256) % 256;
	c.r = (color / 256 / 256) % 256;
	c.t = color / 256 / 256 / 256;
	return (c);
}

int	fdf_color_by_trgb(t_trgb c)
{
	int	color;

	color = c.t;
	color = color * 256 + c.r;
	color = color * 256 + c.g;
	color = color * 256 + c.b;
	return (color);
}

int	fdf_color_mix(int color1, int color2, float ratio)
{
	t_trgb	c1;
	t_trgb	c2;
	t_trgb	c;

	c1 = fdf_color_trgb(color1);
	c2 = fdf_color_trgb(color2);
	c.t = c1.t + ratio * (c2.t - c1.t);
	c.r = c1.r + ratio * (c2.r - c1.r);
	c.g = c1.g + ratio * (c2.g - c1.g);
	c.b = c1.b + ratio * (c2.b - c1.b);
	return (fdf_color_by_trgb(c));
}
