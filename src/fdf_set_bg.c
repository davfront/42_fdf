/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:16:42 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 13:47:08 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_set_bg(t_fdf *fdf)
{
	t_pixel	p1;
	t_pixel	p2;

	p1 = fdf_new_pixel(0, 0, COLOR_BG);
	p2 = fdf_new_pixel(WIN_WIDTH - 1, 0, COLOR_BG);
	while (p1.y < WIN_HEIGHT)
	{
		fdf_draw_line(&fdf->img, p1, p2);
		p1.y++;
		p2.y++;
	}
}
