/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/27 23:57:02 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// main->img->mlx_img = mlx_xpm_file_to_image(main->mlx,
//	"./texture/map2d/floor.xpm",
// 		main->img->width, main->img->height);
// main->img->addr = mlx_get_data_addr(main->img->mlx_img, &(main->img->bpp),
//	&(main->img->line_len),
// 		&(main->img->endian));
// main->picture.wall = mlx_xpm_file_to_image(main->mlx,
//	"./texture/map2d/test.xpm",
// 		&i, &i);

static void	load_texture(t_img *img, t_main *cub, char *texture_path)
{
	img->mlx_img = mlx_xpm_file_to_image(cub->mlx, texture_path, &img->width,
			&img->height);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len,
			&img->endian);
}

void	image_inicialize(t_main *main)
{
	load_texture(&main->picture.p_north, main, main->textures.north);
	load_texture(&main->picture.p_west, main, main->textures.west);
	load_texture(&main->picture.p_east, main, main->textures.east);
	load_texture(&main->picture.p_south, main, main->textures.south);
	load_texture(&main->picture.floor, main,
		"/home/paula/42lisboa/cub_teste/texture/map2d/floor.xpm");
	load_texture(&main->picture.wall, main,
		"/home/paula/42lisboa/cub_teste/texture/map2d/test.xpm");
}
#pragma GCC push_options
#pragma GCC optimize("O0")

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (y >= 0 && x >= 0 && y < img->height && x < img->width)
	{
		dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dest = color;
	}
}

void	ft_mlx_put_image_frame(t_img *frame, int x, int y, t_img *image)
{
	char	*dest;
	char	*src;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++j < image->height)
	{
		while (++i < image->width)
		{
			if ((y + j) > frame->height || (x + i) > frame->width)
				continue;
			dest = frame->addr + ((y + j) * frame->line_len + (x + i) * (frame->bpp / 8));
			src = image->addr + (j  * image->line_len + i * (image->bpp / 8));
			*(unsigned int *)dest = *(unsigned int *)src;
		}
		i = -1;
	}
}

// otimizou o minimap porem para mudar do 3D para 2D assim
// precisa movimentar o player..
void	render_mini(t_main *cub)
{
	static double	angle;
	static double	px;
	static double	py;
	t_coordInt		i;

	angle = 0;
	px = 0;
	py = 0;
	if (cub->player.angle == angle && cub->player.x == px
		&& cub->player.y == py)
		return ;
	angle = cub->player.angle;
	px = cub->player.x;
	py = cub->player.y;
	i.y = -1;
	while (cub->map[++i.y] != NULL)
	{
		i.x = -1;
		while (cub->map[i.y][++i.x] != '\0')
			util_image(cub, i.x, i.y);
	}
	draw_player(cub);
}

// TENHO QUE COLOCAR O CEILING AND FLOOR, ACREDITO QUE POR IMAGEM...
// int x = 0;
// int y = 0;
// while (y < WINDOW_HEIGHT)
// {
// 	x = 0;
// 	if (y > WINDOW_HEIGHT / 2)
// 		while (x < WINDOW_WIDTH)
// 			mlx_pixel_put(cub->mlx, cub->win, x++, y, 0x550000);
// cores em RGB
//((cub->textures.ceiling_rgb.r << 16) + (cub->textures.ceiling_rgb.g << 8)
//			+ (cub->textures.ceiling_rgb.r)));
// 	else
// 	{
// 		while (x < WINDOW_WIDTH)
// 			mlx_pixel_put(cub->mlx, cub->win, x++, y, 0x555500);
// 	}
// 	y++;
// }
void	render_3d(t_main *cub)
{
	int			x_screen;
	t_raycast	ray;
	t_vector	pos;
	double		camera_x;

	x_screen = 0;
	while (x_screen < WINDOW_WIDTH)
	{
		pos.dx = cub->player.x / MINI_WIDTH;
		pos.dy = cub->player.y / MINI_WIDTH;
		camera_x = 2 * x_screen / (double)WINDOW_WIDTH - 1;
		start_ray(&ray, camera_x, cub, pos);
		ray.hit = 0;
		ray_steps(&ray, pos);
		performing_dda(&ray, cub);
		draw_wall(&ray, cub, x_screen, pos);
		x_screen++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.mlx_img, 0, 0);
}

#pragma GCC pop_options

int	render_image(t_main *main)
{
	// if (main->is_mini)
		render_3d(main);
		render_mini(main);
	//else
		// render_3d(main);
	return (0);
}
