/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_free_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/17 11:07:41 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_free_all(t_fdf *fdf)
{
	free(fdf->path);
	fdf_free_map(fdf);
	fdf_free_map_proj(fdf);
	mlx_destroy_window(fdf->mlx, fdf->win);
	ft_free(&fdf->mlx);
}
