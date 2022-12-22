/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:34:28 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_get_line_values(t_fdf *fdf, int y, char *line)
{
	char	**strs;
	int		x;

	strs = ft_split(line, ' ');
	if (!strs)
	{
		fdf_reset(fdf);
		fdf_error_exit(NULL);
	}
	x = 0;
	while (x < fdf->map.size_x)
	{
		fdf->map.values[x][y] = ft_atoi(strs[x]);
		ft_free(strs[x]);
		x++;
	}
	ft_free(strs);
}

void	fdf_get_map_values(t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		y;

	fd = fdf_open_file(fdf->path);
	y = 0;
	line = ft_gnl(fd);
	while (line && *line)
	{
		fdf_get_line_values(fdf, y, line);
		ft_free(line);
		line = ft_gnl(fd);
		y++;
	}
	ft_free(line);
	fdf_close_file(fd);
}
