/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:17:45 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 12:17:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_get_input(int argc, char **argv, t_fdf *fdf)
{
	char		*path;
	char		*filename;
	char		*extension;

	if (argc < 2)
		return (fdf_print_msg("ERROR: Enter the .fdf file path", 0));
	if (argc > 2)
		return (fdf_print_msg("ERROR: Too many arguments", 0));
	path = argv[1];
	filename = ft_strrchr(path, '/');
	if (!filename)
		filename = path;
	else
		filename++;
	if (*filename == '\0')
		return (fdf_print_msg("ERROR: You cannot enter a directory", 0));
	extension = ft_strrchr(path, '.');
	if (!extension || ft_strncmp(extension, ".fdf", 5) != 0)
		return (fdf_print_msg("ERROR: Wrong file format (.fdf expected)", 0));
	fdf->path = path;
	fdf->title = filename;
	return (1);
}
