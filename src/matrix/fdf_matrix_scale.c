/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_scale.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 21:22:47 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_matrix_scale(float m[4][4], float sx, float sy, float sz)
{
	float	ms[4][4];

	fdf_matrix_init(ms);
	ms[0][0] = sx;
	ms[1][1] = sy;
	ms[2][2] = sz;
	fdf_matrix_multiply(m, ms);
}
