/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:34 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:27:05 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_pixel(t_img *img, t_pixel p)
{
	char	*dst;

	if (p.x < 0 || p.x > WIN_WIDTH)
		return ;
	if (p.y < 0 || p.y > WIN_HEIGHT)
		return ;
	dst = img->addr;
	dst += p.y * img->len;
	dst += p.x * (img->bpp / 8);
	*(unsigned int *)dst = p.color;
}
