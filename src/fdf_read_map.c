/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_read_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 16:17:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int	fdf_open_file(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		fdf_error_exit(NULL);
	return (fd);
}

static void	fdf_close_file(int fd)
{
	if (close(fd) == -1)
		fdf_error_exit(NULL);
}

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

static void	fdf_get_map_size(t_fdf *fdf)
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

static void	fdf_alloc_map_values(t_fdf *fdf)
{
	int	i;

	fdf->map.values = ft_calloc(fdf->map.size_x, sizeof(int *));
	if (fdf->map.values == NULL)
		fdf_error_exit(NULL);
	i = 0;
	while (i < fdf->map.size_x)
	{
		fdf->map.values[i] = ft_calloc(fdf->map.size_y, sizeof(int));
		if (fdf->map.values[i] == NULL)
		{
			fdf_reset(fdf);
			fdf_error_exit(NULL);
		}
		i++;
	}
}

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

static void	fdf_get_map_values(t_fdf *fdf)
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

void	fdf_read_map(t_fdf *fdf)
{
	fdf_get_map_size(fdf);
	fdf_alloc_map_values(fdf);
	fdf_get_map_values(fdf);
	fdf_init_view(fdf);
}
