/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_rotate_x.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 19:22:35 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_matrix_rotate_x(float m[4][4], float rx)
{
	float	mrx[4][4];

	fdf_matrix_init(mrx);
	mrx[1][1] = cos(rx);
	mrx[1][2] = -sin(rx);
	mrx[2][1] = sin(rx);
	mrx[2][2] = cos(rx);
	fdf_matrix_multiply(m, mrx);
}
