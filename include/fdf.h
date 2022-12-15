/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/16 00:18:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libft.h>

# define WINDOW_WIDTH	600
# define WINDOW_HEIGHT	300

# define WHITE	0x00FFFFFF
# define RED	0x00FF0000

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_trgb {
	int	t;
	int	r;
	int	g;
	int	b;
}				t_trgb;

typedef struct s_pixel {
	int	x;
	int	y;
	int	color;
}				t_pixel;

t_trgb	fdf_color_trgb(int color);
int		fdf_color_by_trgb(t_trgb c);
int		fdf_color_mix(int color1, int color2, float ratio);

t_pixel	fdf_new_pixel(int x, int y, int color);

void	fdf_draw_pixel(t_data *data, t_pixel p);
void	fdf_draw_line(t_data *data, t_pixel p1, t_pixel p2);

#endif
