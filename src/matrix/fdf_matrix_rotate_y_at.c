/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_rotate_y_at.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 21:23:13 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_matrix_rotate_y_at(float m[4][4], float ry, float x, float y)
{
	fdf_matrix_translate(m, -x, -y);
	fdf_matrix_rotate_y(m, ry);
	fdf_matrix_translate(m, x, y);
}
