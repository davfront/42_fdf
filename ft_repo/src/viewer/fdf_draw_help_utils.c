/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_help_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/17 11:10:39 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_draw_label(t_fdf *fdf, int line, char *label)
{
	mlx_string_put(fdf->mlx, fdf->win, \
		24, HELP_OFFSET_Y + 20 * line, WHITE, label);
}

void	fdf_draw_value(t_fdf *fdf, int line, char *value, int color)
{
	mlx_string_put(fdf->mlx, fdf->win, \
		HELP_VALUE_X, HELP_OFFSET_Y + 20 * line, color, value);
}

void	fdf_draw_info(t_fdf *fdf, int line, char *label, char *value)
{
	fdf_draw_label(fdf, line, label);
	fdf_draw_value(fdf, line, value, WHITE);
}
