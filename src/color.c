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

t_rgb	fdf_color_rgb(int color)
{
	t_rgb	c;

	c.b = color % 256;
	c.g = (color / 256) % 256;
	c.r = (color / 256) / 256;
	return (c);
}

int	fdf_color_int(t_rgb c)
{
	return ((c.r * 256 + c.g) * 256 + c.b);
}

int	fdf_color_mix(int color1, int color2, float ratio)
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	c;

	c1 = fdf_color_rgb(color1);
	c2 = fdf_color_rgb(color2);
	c.r = c1.r + ratio * (c2.r - c1.r);
	c.g = c1.g + ratio * (c2.g - c1.g);
	c.b = c1.b + ratio * (c2.b - c1.b);
	return (fdf_color_int(c));
}
