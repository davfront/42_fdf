/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:55:19 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 21:09:36 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf_data;
	t_fdf	*fdf;

	fdf = &fdf_data;
	fdf_get_input(argc, argv, fdf);
	fdf_read_map(fdf);
	fdf_init_viewer(fdf);
	return (EXIT_SUCCESS);
}
