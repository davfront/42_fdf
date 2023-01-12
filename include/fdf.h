/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/12 17:25:38 by dapereir         ###   ########.fr       */
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

# define WIN_WIDTH		(1024)
# define WIN_HEIGHT		(600)

# define COLOR_BG		(0x00000000)
# define COLOR_TXT		(0x00FFFFFF)
# define COLOR_TOP		(0x00FF0000)
# define COLOR_BOTTOM	(0x000000FF)

# define PI				(3.14159265)

# define ROTATE_STEP	(PI / 50)
# define SCALE_STEP		(1.1)
# define TRANSLATE_STEP	(10)

# define MOUSE_ROT		(PI / 500)

typedef struct s_rgb {
	int	t;
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct s_pixel {
	int	x;
	int	y;
	int	color;
}				t_pixel;

typedef struct s_triangle {
	t_pixel	bot;
	t_pixel	mid;
	t_pixel	top;
}				t_triangle;

typedef struct s_vertice {
	int	x;
	int	y;
	int	z;
	int color;
}				t_vertice;

typedef struct s_map_value {
	int	z;
	int	color;
}				t_map_value;

typedef struct s_map {
	int			size_x;
	int			size_y;
	int			z_min;
	int			z_max;
	int			dz;
	int			has_color;
	t_map_value	**values;
}				t_map;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

typedef struct s_ui {
	int		key_space;
	int		key_z;
	int		mouse_x0;
	int		mouse_y0;
	int		mouse_dx;
	int		mouse_dy;
	int		mouse_left_btn;
	int		mouse_right_btn;
}				t_ui;

typedef struct s_viewer {
	int			perspective;
	int			help;
	int			solid;
	float		zoom;
	float		z_scale;
	int			cx;
	int			cy;
	float		rot[4][4];
	float		proj[4][4];
	t_vertice	**map_proj;
}				t_viewer;

typedef struct s_fdf {
	char		*path;
	char		*title;
	t_map		map;
	void		*mlx;
	void		*win;
	t_img		img;
	t_viewer	viewer;
	t_ui		ui;
}				t_fdf;

// utils
int		fdf_open_file(char *path);
void	fdf_close_file(int fd);
void	fdf_error_exit(char *msg);
int		fdf_get_hex_char_value(char c);

// read
void	fdf_get_input(int argc, char **argv, t_fdf *fdf);
void	fdf_get_map_size(t_fdf *fdf);
void	fdf_alloc_map_values(t_fdf *fdf);
void	fdf_get_map_values(t_fdf *fdf);
void	fdf_get_map_computed_values(t_fdf *fdf);
void	fdf_read_map(t_fdf *fdf);
int		fdf_free_map(t_fdf *fdf);

// color
t_rgb	fdf_color_rgb(int color);
int		fdf_color_by_rgb(t_rgb c);
int		fdf_color_mix(int color1, int color2, float ratio);

// img
t_pixel	fdf_new_pixel(int x, int y, int color);
void	fdf_swap_pixels(t_pixel *p1, t_pixel *p2);
void	fdf_draw_pixel(t_img *img, t_pixel p);
void	fdf_draw_line(t_img *img, t_pixel p1, t_pixel p2);
void	fdf_draw_triangle(t_img *img, t_pixel p1, t_pixel p2, t_pixel p3);

// matrix
void	fdf_matrix_copy(float dst[4][4], float src[4][4]);
void	fdf_matrix_multiply(float m1[4][4], float m2[4][4]);
void	fdf_matrix_init(float m[4][4]);
void	fdf_matrix_scale(float m[4][4], float sx, float sy, float sz);
void	fdf_matrix_translate(float m[4][4], float x, float y);
void	fdf_matrix_rotate_x(float m[4][4], float rx);
void	fdf_matrix_rotate_y(float m[4][4], float ry);
void	fdf_matrix_transform_point(float point[4], float matrix[4][4]);

// viewer
void	fdf_init_ui(t_fdf *fdf);
void	fdf_set_view(t_fdf *fdf, int view);
void	fdf_init_viewer(t_fdf *fdf);
int		fdf_on_keydown(int keycode, t_fdf *fdf);
int		fdf_on_keyup(int keycode, t_fdf *fdf);
int		fdf_on_mouse_down(int button, int x, int y, t_fdf *fdf);
int		fdf_on_mouse_up(int button, int x, int y, t_fdf *fdf);
int		fdf_on_mouse_move(int x, int y, t_fdf *fdf);
void	fdf_hooks(t_fdf *fdf);
void	fdf_update_proj(t_fdf *fdf);
void	fdf_alloc_map_proj(t_fdf *fdf);
void	fdf_get_map_proj(t_fdf *fdf);
void	fdf_free_map_proj(t_fdf *fdf);
void	fdf_draw_map(t_fdf *fdf);
void	fdf_draw_help(t_fdf *fdf);
int		fdf_render_frame(t_fdf *fdf);
void	fdf_start_viewer(t_fdf *fdf);
void	fdf_free_map_proj(t_fdf *fdf);

// exit
void	fdf_free_all(t_fdf *fdf);
int		fdf_exit(t_fdf *fdf);

#endif
