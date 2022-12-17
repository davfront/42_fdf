/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:31:19 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/16 01:38:53 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_print_msg(char *msg, int cb)
{
	ft_putendl_fd(msg, 1);
	return (cb);
}

int	fdf_get_input(int argc, char** argv, t_fdf *fdf)
{
	if (argc < 2)
		return (fdf_print_msg("ERROR: Enter the .fdf file path", 0));
	if (argc > 2)
		return (fdf_print_msg("ERROR: Too many arguments", 0));
	fdf->path = argv[1];
	fdf->filename = ft_strrchr(fdf->path, '/');
	if (!fdf->filename)
		fdf->filename = fdf->path;
	else
		fdf->filename++;	
	fdf->extension = ft_strrchr(fdf->path, '.');
	if (ft_strncmp(fdf->extension, ".fdf", 5) != 0)
		return (fdf_print_msg("ERROR: Wrong file format (.fdf file expected)", 0));
	return (1);
}
