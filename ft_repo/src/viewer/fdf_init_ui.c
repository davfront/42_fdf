/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init_ui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 15:40:07 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_init_ui(t_fdf *fdf)
{
	fdf->ui.key_space = 0;
	fdf->ui.key_z = 0;
	fdf->ui.mouse_x0 = 0;
	fdf->ui.mouse_y0 = 0;
	fdf->ui.mouse_dx = 0;
	fdf->ui.mouse_dy = 0;
	fdf->ui.mouse_left_btn = 0;
	fdf->ui.mouse_right_btn = 0;
}
