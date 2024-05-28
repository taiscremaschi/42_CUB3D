/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:31:23 by paula             #+#    #+#             */
/*   Updated: 2024/05/28 09:32:43 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

#pragma GCC push_options
#pragma GCC optimize("O0")

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
}

#pragma GCC pop_options

int	render_image(t_main *main)
{
	if (main->is_mini)
	{
		ft_mlx_put_image_frame(&main->img, 0, 0, &main->picture.clean);
		render_mini(main);
	}
	else
		render_3d(main);
	mlx_put_image_to_window(main->mlx, main->win, main->img.mlx_img, 0, 0);
	return (0);
}
