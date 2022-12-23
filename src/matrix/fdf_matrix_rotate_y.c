/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_rotate_y.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 21:22:00 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_matrix_rotate_y(float m[4][4], float ry)
{
	float	mry[4][4];

	fdf_matrix_init(mry);
	mry[0][0] = cos(ry);
	mry[0][2] = sin(ry);
	mry[2][0] = -sin(ry);
	mry[2][2] = cos(ry);
	fdf_matrix_multiply(m, mry);
}
