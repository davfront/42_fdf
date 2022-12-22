/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 18:32:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_count_line_values(char *line)
{
	int		count;

	if (!line)
		return (0);
	count = 0;
	while (*line)
	{
		if (*line == ' ' || *line == '\n')
			line++;
		else if (ft_isdigit(*line) || (*line == '-' && ft_isdigit(*(line + 1))))
		{
			count++;
			line++;
			while (ft_isdigit(*line))
				line++;
		}
		else
			return (0);
	}
	return (count);
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
