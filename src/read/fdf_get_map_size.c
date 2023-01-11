/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/03 21:06:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_count_line_values(char *line)
{
	char	*bl;
	char	**strs;
	int		i;

	if (!line)
		return (0);
	bl = ft_strchr(line, '\n');
	if (bl)
		*bl = '\0';
	strs = ft_split(line, ' ');
	if (!strs)
		fdf_error_exit(NULL);
	i = 0;
	while (strs[i])
	{
		ft_free(strs[i]);
		i++;
	}
	ft_free(strs);
	return (i);
}

void	fdf_get_map_size(t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		x;

	fdf->map.size_x = 0;
	fdf->map.size_y = 0;
	fd = fdf_open_file(fdf->path);
	line = ft_gnl(fd);
	while (line && *line)
	{
		fdf->map.size_y++;
		x = fdf_count_line_values(line);
		if (x < 2 || (fdf->map.size_y > 1 && x != fdf->map.size_x))
			fdf_error_exit("Invalid file content");
		if (fdf->map.size_y == 1)
			fdf->map.size_x = x;
		ft_free(line);
		line = ft_gnl(fd);
	}
	ft_free(line);
	if (fdf->map.size_y < 2)
		fdf_error_exit("Invalid file content");
	fdf_close_file(fd);
}
