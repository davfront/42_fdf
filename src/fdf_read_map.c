/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 14:13:11 by dapereir         ###   ########.fr       */
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

static int	fdf_get_map_size(t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		x_temp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	fd = open(fdf->path, O_RDONLY);
	if (fd == -1)
		return (fdf_print_msg("ERROR: The file cannot be opened", 0));
	line = ft_gnl(fd);
	while (line && *line)
	{
		y++;
		x_temp = fdf_count_line_values(line);
		if (x_temp < 2 || (y > 1 && x_temp != x))
			return (fdf_print_msg("ERROR: The file content is not valid", 0));
		if (y == 1)
			x = x_temp;
		ft_free(line);
		line = ft_gnl(fd);
	}
	ft_free(line);
	if (y < 2)
		return (fdf_print_msg("ERROR: The file content is not valid", 0));
	fdf->map.size_x = x;
	fdf->map.size_y = y;
	if (close(fd) == -1)
		return (fdf_print_msg("ERROR: Closing the file failed", 0));
	return (1);
}

static int	fdf_alloc_map_values(t_fdf *fdf)
{
	int	i;

	fdf->map.values = ft_calloc(fdf->map.size_x, sizeof(int *));
	if (fdf->map.values == NULL)
		return (fdf_print_msg("ERROR: Malloc failed", 0));
	i = 0;
	while (i < fdf->map.size_x)
	{
		fdf->map.values[i] = ft_calloc(fdf->map.size_y, sizeof(int));
		if (fdf->map.values[i] == NULL)
		{
			fdf_free(fdf);
			return (fdf_print_msg("ERROR: Malloc failed", 0));
		}
		i++;
	}
	return (1);
}

static int	fdf_get_map_values(t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**strs;
	int		x;
	int		y;

	fd = open(fdf->path, O_RDONLY);
	if (fd == -1)
		return (fdf_print_msg("ERROR: The file cannot be opened", 0));
	y = 0;
	line = ft_gnl(fd);
	while (line && *line)
	{
		strs = ft_split(line, ' ');
		if (!strs)
		{
			// TODO: free map
			return (fdf_print_msg("ERROR: Split failed", 0));
		}
		x = 0;
		while (x < fdf->map.size_x)
		{
			fdf->map.values[x][y] = ft_atoi(strs[x]);
			x++;
		}
		// TODO: free split
		ft_free(line);
		line = ft_gnl(fd);
		y++;
	}
	ft_free(line);
	if (close(fd) == -1)
		return (fdf_print_msg("ERROR: Closing the file failed", 0));
	return (1);
}

static void	fdf_init_view(t_fdf *fdf)
{
	float		x_scale;
	float		y_scale;

	x_scale = (WIN_WIDTH * 0.8 / (fdf->map.size_x - 1));
	y_scale = (WIN_HEIGHT * 0.8 / (fdf->map.size_y - 1));
	fdf->zoom = fmin(x_scale, y_scale);
	fdf->z_scale = 0.2;

	fdf->x0 = (WIN_WIDTH - (fdf->map.size_x - 1) * fdf->zoom) / 2;
	fdf->y0 = (WIN_HEIGHT - (fdf->map.size_y - 1) * fdf->zoom) / 2;

	fdf->rx = PI / 5;
	fdf->ry = PI / 4;
}

int	fdf_read_map(t_fdf *fdf)
{
	if (!fdf_get_map_size(fdf))
		return (0);
	if (!fdf_alloc_map_values(fdf))
		return (0);
	if (!fdf_get_map_values(fdf))
		return (0);
	fdf_init_view(fdf);
	return (1);
}
