/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2023/01/17 16:22:57 by dapereir         ###   ########.fr       */
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
#  define HELP_OFFSET_Y	(0)
#  define HELP_VALUE_X	(220)
#  define HELP_WIDTH	(590)
# else
#  include <key_linux.h>
#  define HELP_OFFSET_Y	(20)
#  define HELP_VALUE_X	(160)
#  define HELP_WIDTH	(390)
# endif

# define WIN_WIDTH	(1024)
# define WIN_HEIGHT	(600)

# define BLACK		(0x00000000)
# define WHITE		(0x00FFFFFF)
# define RED		(0x00FF0000)
# define GREEN		(0x0000FF00)
# define BLUE		(0x000000FF)

# define PI			(3.14159265)

typedef struct s_rgb {
	int	t;
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct s_pixel {
	int		x;
	int		y;
	int		color;
	float	z;
}				t_pixel;

typedef struct s_triangle {
	t_pixel	bot;
	t_pixel	mid;
	t_pixel	top;
}				t_triangle;

typedef struct s_vertice {
	float	x;
	float	y;
	float	z;
	int		color;
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

typedef enum e_color {
	DISABLED,
	MAP_VALUES,
	Z_GRADIENT
}				t_color;

typedef enum e_render {
	WIREFRAME,
	WIREFRAME_NO_HIDDEN,
	SOLID
}				t_render;

typedef struct s_viewer {
	int			perspective;
	int			help;
	t_color		color;
	t_render	render;
	float		zoom_base;
	float		zoom;
	float		z_scale_base;
	float		z_scale;
	int			cx;
	int			cy;
	float		z_cam;
	float		rot[4][4];
	float		proj[4][4];
	t_vertice	**map_proj;
	int			x_rev;
	int			y_rev;
	int			z_rev;
	int			x_loop_first;
}				t_viewer;

typedef struct s_fdf {
	char		*path;
	char		*title;
	t_map		map;
	void		*mlx;
	void		*win;
	t_img		img;
	float		z_buffer[WIN_WIDTH][WIN_HEIGHT];
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
t_pixel	fdf_vertice_to_pixel(t_vertice v);
void	fdf_swap_pixels(t_pixel *p1, t_pixel *p2);
void	fdf_draw_pixel(t_fdf *fdf, t_pixel p);
void	fdf_draw_line(t_fdf *fdf, t_pixel p1, t_pixel p2);
void	fdf_draw_triangle(t_fdf *fdf, t_pixel p1, t_pixel p2, t_pixel p3);
void	fdf_init_z_buffer(t_fdf *fdf);

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
void	fdf_draw_face(t_fdf *fdf, int x, int y);
void	fdf_draw_map(t_fdf *fdf);
void	fdf_draw_label(t_fdf *fdf, int line, char *label);
void	fdf_draw_value(t_fdf *fdf, int line, char *value, int color);
void	fdf_draw_info(t_fdf *fdf, int line, char *label, char *value);
void	fdf_draw_help(t_fdf *fdf);
int		fdf_render_frame(t_fdf *fdf);
void	fdf_start_viewer(t_fdf *fdf);
void	fdf_free_map_proj(t_fdf *fdf);

// exit
void	fdf_free_all(t_fdf *fdf);
int		fdf_exit(t_fdf *fdf);

#endif
