/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 09:45:32 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi_hex(char *str)
{
	char	hex[17];
	int		n;
	char	*s;

	ft_strlcpy(hex, "0123456789ABCDEF", 17);
	n = 0;
	s = ft_strchr(hex, ft_toupper(*str));
	while (s && *s)
	{
		n = n * 16 + (s - hex);
		str++;
		s = ft_strchr(hex, ft_toupper(*str));
	}
	return (n);
}

static void	fdf_get_line_values(t_fdf *fdf, int y, char *line)
{
	char	**strs;
	int		x;
	char	*substr;

	strs = ft_split(line, ' ');
	if (!strs)
	{
		fdf_reset(fdf);
		fdf_error_exit(NULL);
	}
	x = 0;
	while (x < fdf->map.size_x)
	{
		fdf->map.values[x][y].z = ft_atoi(strs[x]);
		fdf->map.values[x][y].color = -1;
		substr = ft_strnstr(strs[x], ",0x", ft_strlen(strs[x]));
		if (substr)
			fdf->map.values[x][y].color = ft_atoi_hex(substr + 3);
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
