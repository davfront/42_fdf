/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix_rotate_x_at.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:49:11 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/23 19:23:09 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_matrix_rotate_x_at(float m[4][4], float rx, float x, float y)
{
	fdf_matrix_translate(m, -x, -y);
	fdf_matrix_rotate_x(m, rx);
	fdf_matrix_translate(m, x, y);
}
