/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:35:43 by dapereir          #+#    #+#             */
/*   Updated: 2022/12/22 10:50:50 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_set_bg(t_fdf *fdf)
{
	int		i;
	int 	j;
	t_pixel	p;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			p.x = i;
			p.y = j;
			p.color = COLOR_BG;
			fdf_draw_pixel(&fdf->img, p);
			j++;
		} 
		i++;
	} 
}

void	fdf_map_to_pixel(t_fdf *fdf, int x, int y, t_pixel *p)
{
	t_vector	v;
	t_vector	v2;

	v.x = x * fdf->h_scale;
	v.y = y * fdf->h_scale;
	v.z = fdf->map.values[x][y];
	
	// translate center of map to origin
	v.x -= fdf->map.size_x * fdf->h_scale / 2;
	v.y -= fdf->map.size_y * fdf->h_scale / 2;

	// rotate X by 90deg
	v2.x = v.x;
	v2.y = -v.z;
	v2.z = v.y;
	v = v2;

	// rotate Y by 45deg
	v2.x = cos(fdf->ry) * v.x - sin(fdf->ry) * v.z;
	v2.y = v.y;
	v2.z = sin(fdf->ry) * v.x + cos(fdf->ry) * v.z;
	v = v2;

	// rotate X by 35deg
	v2.x = v.x;
	v2.y = cos(fdf->rx) * v.y + sin(fdf->rx) * v.z;
	v2.z = -sin(fdf->rx) * v.y + cos(fdf->rx) * v.z;
	v = v2;

	// translate to center of screen
	v.x += WIN_WIDTH / 2;
	v.y += WIN_HEIGHT / 2;

	p->color = fdf_color_mix(COLOR_BOTTOM, COLOR_TOP, fdf->map.values[x][y] / 10);
	p->x = v.x;
	p->y = v.y;
}

void	fdf_draw_x_edge(t_fdf *fdf, int x, int y)
{
	t_pixel	p1;
	t_pixel	p2;

	if (x < 0 || x > fdf->map.size_x - 2)
		return ;
	fdf_map_to_pixel(fdf, x, y, &p1);
	fdf_map_to_pixel(fdf, x + 1, y, &p2);
	fdf_draw_line(&fdf->img, p1, p2);
}

void	fdf_draw_y_edge(t_fdf *fdf, int x, int y)
{
	t_pixel	p1;
	t_pixel	p2;

	if (y < 0 || y > fdf->map.size_y - 2)
		return ;
	fdf_map_to_pixel(fdf, x, y, &p1);
	fdf_map_to_pixel(fdf, x, y + 1, &p2);
	fdf_draw_line(&fdf->img, p1, p2);
}

void	fdf_draw_frame(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf_set_bg(fdf);
	x = 0;
	while (x < fdf->map.size_x)
	{
		y = 0;
		while (y < fdf->map.size_y)
		{
			fdf_draw_x_edge(fdf, x, y);
			fdf_draw_y_edge(fdf, x, y);
			y++;
		}
		x++;
	}
}

int	fdf_render_frame(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, \
		&fdf->img.len, &fdf->img.endian);
	fdf_draw_frame(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	return (0);
}

int	fdf_free(t_fdf *fdf)
{
	if (fdf->map.values) {
		while (fdf->map.size_x > 0)
		{
			if (fdf->map.values[fdf->map.size_x - 1])
				free(fdf->map.values[fdf->map.size_x - 1]);
			fdf->map.size_x--;
		}
		free(fdf->map.values);
	}
	fdf->map.values = NULL;
	fdf->map.size_x = 0;
	fdf->map.size_y = 0;
	return (0);
}

int	fdf_exit(t_fdf *fdf)
{
	fdf_free(fdf);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->mlx);
	exit(1);
	return (0);
}

int	fdf_key_hook(int keycode, t_fdf *fdf)
{
	// esc
	if (keycode == KEY_ESC)
		fdf_exit(fdf);
	// left
	if (keycode == KEY_LEFT)
		fdf->ry -= 0.1;
	// right
	if (keycode == KEY_RIGHT)
		fdf->ry += 0.1;
	// up
	if (keycode == KEY_UP)
		fdf->rx -= 0.1;
	// down
	if (keycode == KEY_DOWN)
		fdf->rx += 0.1;
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	// when key pressed
	mlx_key_hook(fdf->win, fdf_key_hook, fdf);
	
	// when window closed
	mlx_hook(fdf->win, 17, 1L<<0, fdf_exit, fdf);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf_data;
	t_fdf	*fdf;

	fdf = &fdf_data;
	if (!fdf_get_input(argc, argv, fdf))
		return (1);
	if (!fdf_read(fdf))
		return (1);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, fdf->title);
	fdf_hooks(fdf);
	mlx_loop_hook(fdf->mlx, fdf_render_frame, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
