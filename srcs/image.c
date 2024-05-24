/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/24 09:18:44 by paula            ###   ########.fr       */
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
void	image_inicialize(t_main *main)
{
	int	i;

	main->picture.p_north = mlx_xpm_file_to_image(main->mlx,
			main->textures.north, &i, &i);
	main->picture.p_south = mlx_xpm_file_to_image(main->mlx,
			main->textures.south, &i, &i);
	main->picture.p_west = mlx_xpm_file_to_image(main->mlx, main->textures.west,
			&i, &i);
	main->picture.p_east = mlx_xpm_file_to_image(main->mlx, main->textures.east,
			&i, &i);
	main->picture.floor = mlx_xpm_file_to_image(main->mlx,
			"./texture/map2d/floor.xpm", &i, &i);
	main->picture.wall = mlx_xpm_file_to_image(main->mlx,
			"./texture/map2d/test.xpm", &i, &i);
	main->picture.player2d = mlx_xpm_file_to_image(main->mlx,
			"./images/player2d_2.xpm", &i, &i);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (y >= 0 && x >= 0 && y < WINDOW_HEIGHT && x < WINDOW_WIDTH)
	{
		dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dest = color;
	}
}
#pragma GCC push_options
#pragma GCC optimize("O0")

// otimizou o minimap porem para mudar do 3D para 2D assim 
//precisa movimentar o player..
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
// 	else
// 	{
// 		while (x < WINDOW_WIDTH)
// 			mlx_pixel_put(cub->mlx, cub->win, x++, y, 0x555500);
// 	}
// 	y++;
// }
void	render_3D(t_main *cub)
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
}

#pragma GCC pop_options

int	render_image(t_main *main)
{
	if (main->is_mini)
		render_mini(main);
	else
		printf("teste\n");
		//render_3D(main);
	return (0);
}
