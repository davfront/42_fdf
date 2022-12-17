/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 01:34:49 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/16 08:37:12 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_parse(int fd)
{
	char	*line;
	int		line_len;
	char	**values;
	int		x;
	int		y;

	y = 0;
	line = ft_gnl(fd);
	line_len = ft_strlen(line);
	if (line[line_len - 1] != '\n')
		return (0);
	while (line)
	{
		values = ft_split(line, ' ');
		if (!values)
			return (0);
		x = 0;
		while (values[x])
		{
			ft_putnbr_fd(ft_atoi(values[x]), 1);
			ft_putchar_fd('\t', 1);
			x++;
		}
		ft_putchar_fd('\n', 1);
		y++;
		line = ft_gnl(fd);
	}
	return (1);
}

int	fdf_read(t_fdf *fdf)
{
	int fd;

	fd = open(fdf->path, O_RDONLY);
	if (fd == -1)
		return (fdf_print_msg("ERROR: The file cannot be opened", 0));
	if (!fdf_parse(fd))
		return (fdf_print_msg("ERROR: Wrong data", 0));
	if (close(fd) == -1)
		return (fdf_print_msg("ERROR: Closing the file failed", 0));
	return (1);
}