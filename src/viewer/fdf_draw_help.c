/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/11 15:54:09 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_text(t_fdf *fdf, int line, char *text)
{
	mlx_string_put(fdf->mlx, fdf->win, 20, 20 + 20 * line, COLOR_TXT, text);
}

void	fdf_draw_help(t_fdf *fdf)
{
	int	line;

	line = 1;
	fdf_draw_text(fdf, line++, "[H] Help");
	if (!fdf->opt.help)
		return ;
	line++;
	fdf_draw_text(fdf, line++, "[0] Isometric view");
	fdf_draw_text(fdf, line++, "[1] Z-axis view");
	fdf_draw_text(fdf, line++, "[2] X-axis view");
	fdf_draw_text(fdf, line++, "[3] Y-axis view");
	line++;
	fdf_draw_text(fdf, line++, "[P] Projection mode \
(Orthogonal <-> Perspective)");
	fdf_draw_text(fdf, line++, "[R] Rendering mode \
(Wireframe <-> Solid)");
	line++;
	fdf_draw_text(fdf, line++, "[+] Zoom in");
	fdf_draw_text(fdf, line++, "[-] Zoom out");
	line++;
	fdf_draw_text(fdf, line++, "[Z] + [+] Scale Z-axis Up");
	fdf_draw_text(fdf, line++, "[Z] + [-] Scale Z-axis Down");
	line++;
	fdf_draw_text(fdf, line++, "[Arrow] Rotate");
	line++;
	fdf_draw_text(fdf, line++, "[Space] + [Arrow] Translate");
}
