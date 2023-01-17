/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_by_rgb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:02:58 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:15:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_color_by_rgb(t_rgb c)
{
	int	color;

	color = c.r;
	color = color * 256 + c.g;
	color = color * 256 + c.b;
	return (color);
}
