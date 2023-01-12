/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_map_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 12:02:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


static int	fdf_get_hex_char_value(char c)
{
	char	hex[17];
	char	*s;

	if (!c)
		return (-1);
	ft_strlcpy(hex, "0123456789ABCDEF", 17);
	s = ft_strchr(hex, ft_toupper(c));
	if (s)
		return (s - hex);
	return (-1);
}

static int	fdf_is_entry_valid(char *s)
{
	if (!s || !*s)
		return (0);
	if (*s == '-' || *s == '+')
		s++;
	if (!ft_isdigit(*s))
		return (0);
	s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == ',')
	{
		if (*(s + 1) != '0' || *(s + 2) != 'x')
			return (0);
		s += 3;
		if (fdf_get_hex_char_value(*s) == -1)
			return (0);
		s++;
		while (fdf_get_hex_char_value(*s) != -1)
			s++;
	}
	if (*s != '\0' && *s != '\n')
		return (0);
	return (1);
}

static int	ft_atoi_hex(char *str)
{
	int		n;
	int		i;

	n = 0;
	i = fdf_get_hex_char_value(*str);
	while (i != -1)
	{
		n = n * 16 + i;
		str++;
		i = fdf_get_hex_char_value(*str);
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
		fdf_free_map(fdf);
		fdf_error_exit(NULL);
	}
	x = 0;
	while (x < fdf->map.size_x)
	{
		if (!fdf_is_entry_valid(strs[x]))
		{
			ft_free((void **)&strs[x]);
			fdf_free_map(fdf);
			fdf_error_exit("Invalid file content");
		}
		fdf->map.values[x][y].z = ft_atoi(strs[x]);
		fdf->map.values[x][y].color = -1;
		substr = ft_strnstr(strs[x], ",0x", ft_strlen(strs[x]));
		if (substr)
			fdf->map.values[x][y].color = ft_atoi_hex(substr + 3);
		ft_free((void **)&strs[x]);
		x++;
	}
	ft_free((void **)&strs);
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
		ft_free((void **)&line);
		line = ft_gnl(fd);
		y++;
	}
	ft_free((void **)&line);
	fdf_close_file(fd);
}
