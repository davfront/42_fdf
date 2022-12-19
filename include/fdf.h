/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/19 15:49:40 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <math.h>

# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif

# define WIN_WIDTH		800
# define WIN_HEIGHT		600
# define COLOR_TOP		0x00FF0000
# define COLOR_BOTTOM	0x000000FF
# define PI				3.14159265

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

typedef struct s_vector {
	int	x;
	int	y;
	int	z;
}				t_vector;

typedef struct s_map {
	int	size_x;
	int	size_y;
	int	**values;
}				t_map;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

typedef struct s_fdf {
	char	*path;
	char	*title;
	t_map	map;
	void	*mlx;
	void	*win;
	float	h_scale;
	int		x0;
	int		y0;
	float	rx;
	float	ry;
	t_img	img;
}				t_fdf;

int		fdf_print_msg(char *msg, int cb);
int		fdf_get_input(int argc, char **argv, t_fdf *fdf);

int		fdf_read(t_fdf *fdf);

t_trgb	fdf_color_trgb(int color);
int		fdf_color_by_trgb(t_trgb c);
int		fdf_color_mix(int color1, int color2, float ratio);

t_pixel	fdf_new_pixel(int x, int y, int color);

void	fdf_draw_pixel(t_img *img, t_pixel p);
void	fdf_draw_line(t_img *img, t_pixel p1, t_pixel p2);

int		fdf_free(t_fdf *fdf);

#endif
