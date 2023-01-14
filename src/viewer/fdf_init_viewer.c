/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_viewer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/14 18:45:22 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_viewer(t_fdf *fdf)
{
	fdf->viewer.z_cam = fmax(WIN_WIDTH, WIN_HEIGHT);
	fdf->viewer.perspective = 0;
	fdf->viewer.help = 0;
	fdf->viewer.color = DISABLED;
	fdf->viewer.render = WIREFRAME;
	fdf_set_view(fdf, 0);
}
