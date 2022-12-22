/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:17:45 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 15:13:27 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_get_input(int argc, char **argv, t_fdf *fdf)
{
	char		*path;
	char		*filename;
	char		*extension;

	if (argc < 2)
		fdf_error_exit("Missing argument (.fdf file expected)");
	if (argc > 2)
		fdf_error_exit("Too many arguments");
	path = argv[1];
	filename = ft_strrchr(path, '/');
	if (!filename)
		filename = path;
	else
		filename++;
	if (*filename == '\0')
		fdf_error_exit("Wrong argument (.fdf file expected)");
	extension = ft_strrchr(path, '.');
	if (!extension || ft_strncmp(extension, ".fdf", 5) != 0)
		fdf_error_exit("Wrong argument (.fdf file expected)");
	fdf->path = path;
	fdf->title = filename;
}
