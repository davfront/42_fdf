/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:14 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/17 09:16:24 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

# define WINDOW_WIDTH	500
# define WINDOW_HEIGHT	500

# define WHITE	0x00FFFFFF
# define RED	0x00FF0000

typedef struct s_fdf {
	char	*path;
	char	*filename;
	char	*extension;
}				t_fdf;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

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

int		fdf_print_msg(char *msg, int cb);
int		fdf_get_input(int argc, char** argv, t_fdf *fdf);

int		fdf_read(t_fdf *fdf);

t_trgb	fdf_color_trgb(int color);
int		fdf_color_by_trgb(t_trgb c);
int		fdf_color_mix(int color1, int color2, float ratio);

t_pixel	fdf_new_pixel(int x, int y, int color);

void	fdf_draw_pixel(t_img *img, t_pixel p);
void	fdf_draw_line(t_img *img, t_pixel p1, t_pixel p2);

#endif
