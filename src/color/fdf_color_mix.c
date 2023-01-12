/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_mix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:26 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 09:31:07 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (fdf_color_by_rgb(c));
}
