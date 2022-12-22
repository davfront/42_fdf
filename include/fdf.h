/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 21:07:15 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE	1
# endif

# ifndef STDERR
#  define STDERR		2
# endif

# define WIN_WIDTH		800
# define WIN_HEIGHT		600

# define COLOR_BG		0x00000000
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
	float	zoom;
	float	z_scale;
	int		x0;
	int		y0;
	float	rx;
	float	ry;
	t_img	img;
}				t_fdf;

// utils
int		fdf_open_file(char *path);
void	fdf_close_file(int fd);
void	fdf_error_exit(char *msg);

// read
void	fdf_get_input(int argc, char **argv, t_fdf *fdf);
void	fdf_get_map_size(t_fdf *fdf);
void	fdf_alloc_map_values(t_fdf *fdf);
void	fdf_get_map_values(t_fdf *fdf);
void	fdf_read_map(t_fdf *fdf);

// color
t_trgb	fdf_color_trgb(int color);
int		fdf_color_by_trgb(t_trgb c);
int		fdf_color_mix(int color1, int color2, float ratio);

// img
t_pixel	fdf_new_pixel(int x, int y, int color);
void	fdf_draw_pixel(t_img *img, t_pixel p);
void	fdf_draw_line(t_img *img, t_pixel p1, t_pixel p2);
void	fdf_set_bg(t_fdf *fdf);

// viewer
void	fdf_init_viewer(t_fdf *fdf);
void	fdf_hooks(t_fdf *fdf);
int		fdf_render_frame(t_fdf *fdf);

// exit
int		fdf_reset(t_fdf *fdf);
int		fdf_exit(t_fdf *fdf);

#endif
