/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/02 09:24:38 by dapereir         ###   ########.fr       */
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

# define WIN_WIDTH		1024
# define WIN_HEIGHT		600

# define COLOR_BG		0x00000000
# define COLOR_TXT		0x00FFFFFF
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
	int	z_min;
	int	z_max;
	int	**values;
}				t_map;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

typedef struct s_opt {
	int		perspective;
	int		help;
}				t_opt;

typedef struct s_fdf {
	char	*path;
	char	*title;
	t_map	map;
	void	*mlx;
	void	*win;
	t_img	img;
	t_pixel	**proj;
	float	mt[4][4];
	t_opt	opt;
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
void	fdf_get_map_zminmax(t_fdf *fdf);
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

// matrix
void	fdf_matrix_copy(float dst[4][4], float src[4][4]);
void	fdf_matrix_multiply(float m1[4][4], float m2[4][4]);
void	fdf_matrix_init(float m[4][4]);
void	fdf_matrix_scale(float m[4][4], float sx, float sy, float sz);
void	fdf_matrix_translate(float m[4][4], float x, float y);
void	fdf_matrix_rotate_x(float m[4][4], float rx);
void	fdf_matrix_rotate_x_at(float m[4][4], float rx, float x, float y);
void	fdf_matrix_rotate_y(float m[4][4], float ry);
void	fdf_matrix_rotate_y_at(float m[4][4], float ry, float x, float y);
void	fdf_matrix_transform_point(float point[4], float matrix[4][4]);

// viewer
void	fdf_init_viewer(t_fdf *fdf);
void	fdf_init_mt(t_fdf *fdf, int view);
void	fdf_hooks(t_fdf *fdf);
int		fdf_render_frame(t_fdf *fdf);
void	fdf_start_viewer(t_fdf *fdf);

// exit
int		fdf_reset(t_fdf *fdf);
int		fdf_exit(t_fdf *fdf);

#endif
