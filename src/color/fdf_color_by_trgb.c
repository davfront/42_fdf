/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_by_trgb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 18:02:58 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:15:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_color_by_trgb(t_trgb c)
{
	int	color;

	color = c.t;
	color = color * 256 + c.r;
	color = color * 256 + c.g;
	color = color * 256 + c.b;
	return (color);
}
