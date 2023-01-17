/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:52:54 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/14 22:02:10 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_help_controls(t_fdf *fdf)
{
	int	line;

	line = 1;
	fdf_draw_label(fdf, line++, "CONTROLS");
	line++;
	fdf_draw_info(fdf, line++, "Quit Help", "[H]");
	fdf_draw_info(fdf, line++, "Quit Viewer", "[Esc]");
	line++;
	fdf_draw_info(fdf, line++, "Isometric view", "[0]");
	fdf_draw_info(fdf, line++, "Z-axis view", "[1]");
	fdf_draw_info(fdf, line++, "X-axis view", "[2]");
	fdf_draw_info(fdf, line++, "Y-axis view", "[3]");
	line++;
	fdf_draw_info(fdf, line++, "Color mode", "[C]");
	fdf_draw_info(fdf, line++, "Rendering mode", "[R]");
	fdf_draw_info(fdf, line++, "Perspective", "[P]");
	line++;
	fdf_draw_info(fdf, line++, "Rotate", "[Arrow]  /  [Mouse Right]");
	fdf_draw_info(fdf, line++, "Translate", \
		"[Space] + [Arrow]  /  [Mouse Left]");
	fdf_draw_info(fdf, line++, "Zoom in", "[+]  /  [Mouse Scroll Down]");
	fdf_draw_info(fdf, line++, "Zoom out", "[-]  /  [Mouse Scroll Up]");
	fdf_draw_info(fdf, line++, "Scale Z-axis up", "[Z] + [+]");
	fdf_draw_info(fdf, line++, "Scale Z-axis down", "[Z] + [-]");
}

void	fdf_draw_help_settings(t_fdf *fdf)
{
	int	line;

	line = 23;
	fdf_draw_label(fdf, line++, "SETTINGS");
	line++;
	fdf_draw_label(fdf, line, "Color mode");
	if (fdf->viewer.color == MAP_VALUES)
		fdf_draw_value(fdf, line++, "MAP_VALUES", GREEN);
	else if (fdf->viewer.color == Z_GRADIENT)
		fdf_draw_value(fdf, line++, "Z_GRADIENT", GREEN);
	else
		fdf_draw_value(fdf, line++, "DISABLED", RED);
	fdf_draw_label(fdf, line, "Rendering mode");
	if (fdf->viewer.render == WIREFRAME_NO_HIDDEN)
		fdf_draw_value(fdf, line++, "WIREFRAME_NO_HIDDEN", GREEN);
	else if (fdf->viewer.render == SOLID)
		fdf_draw_value(fdf, line++, "SOLID", GREEN);
	else
		fdf_draw_value(fdf, line++, "WIREFRAME", GREEN);
	fdf_draw_label(fdf, line, "Perspective");
	if (fdf->viewer.perspective)
		fdf_draw_value(fdf, line++, "ENABLED", GREEN);
	else
		fdf_draw_value(fdf, line++, "DISABLED", RED);
}

void	fdf_draw_help(t_fdf *fdf)
{
	if (!fdf->viewer.help)
		return ;
	fdf_draw_help_controls(fdf);
	fdf_draw_help_settings(fdf);
}
