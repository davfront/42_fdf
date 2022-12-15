/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/14 16:35:17 by dapereir         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>

# define WHITE	0x00FFFFFF
# define RED		0x00FF0000

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_trgb {
	int		t;
	int		r;
	int		g;
	int		b;
}				t_trgb;

typedef struct s_point {
	unsigned int	x;
	unsigned int	y;
}				t_point;

t_trgb	fdf_color_trgb(int color);
int		fdf_color_by_trgb(t_trgb c);
int		fdf_color_mix(int color1, int color2, float ratio);
t_point	fdf_point(unsigned int x, unsigned int y);
void	fdf_draw_pixel(t_data *data, t_point p, int color);
void	fdf_draw_line(t_data *data, t_point p1, t_point p2, int color1, int color2);

#endif
