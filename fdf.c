#include <mlx.h>
#include <stdio.h>

#define WHITE	0x00FFFFFF
#define RED		0x00FF0000

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_rgb {
	int		r;
	int		g;
	int		b;
}				t_rgb;

typedef struct s_point {
	unsigned int	x;
	unsigned int	y;
}				t_point;

t_point	fdf_point(unsigned int x, unsigned int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	fdf_plot(t_data *data, t_point p, int color)
{
	char	*dst;

	dst = data->addr;
	dst += p.y * data->line_length;
	dst += p.x * (data->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

/*
https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
*/
float	fdf_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

t_rgb	fdf_color_rgb(int color)
{
	t_rgb	c;

	c.b = color % 256;
	c.g = (color / 256) % 256;
	c.r = (color / 256) / 256;
	return (c);
}

int	fdf_color_int(t_rgb c)
{
	return ((c.r * 256 + c.g) * 256 + c.b);
}

int		fdf_color_mix(int color1, int color2, float ratio)
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	c;

	c1 = fdf_color_rgb(color1);
	c2 = fdf_color_rgb(color2);
	c.r = c1.r + ratio * (c2.r - c1.r);
	c.g = c1.g + ratio * (c2.g - c1.g);
	c.b = c1.b + ratio * (c2.b - c1.b);
	return (fdf_color_int(c));
}

void	fdf_drawline(t_data *data, t_point p1, t_point p2, int color1, int color2)
{
	float	len;
	float	len_x;
	float	len_y;
	float	delta_x;
	float	delta_y;
	int		i;
	int		color;
	t_point	p;

	if (p1.x == p2.x && p1.y == p2.y)
	{
		fdf_plot(data, p1, WHITE);
		return;
	}
	len_x = fdf_abs((float)p2.x - (float)p1.x);
	len_y = fdf_abs((float)p2.y - (float)p1.y);
	len = len_x;
	if (len < len_y)
		len = len_y;
	delta_x = ((float)p2.x - (float)p1.x) / len;
	delta_y = ((float)p2.y - (float)p1.y) / len;
	i = 0;
	while (i < len)
	{
		p.x = p1.x + (int)(i * delta_x);
		p.y = p1.y + (int)(i * delta_y);
		color = fdf_color_mix(color1, color2, (float)i / len);
		fdf_plot(data, p, color);
		i++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	fdf_drawline(&img, fdf_point(20, 20), fdf_point(200, 50), WHITE, RED);
	fdf_drawline(&img, fdf_point(200, 50), fdf_point(200, 200), RED, WHITE);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
