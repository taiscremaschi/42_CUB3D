/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:31:23 by paula             #+#    #+#             */
/*   Updated: 2024/05/28 10:29:41 by paula            ###   ########.fr       */
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
			put_2d_image(cub, i.x, i.y);
	}
	draw_player(cub);
}

void	put_ceiling_floor(t_main *cub)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		if (y < (WINDOW_HEIGHT / 2))
			while (x < WINDOW_WIDTH)
				ft_mlx_pixel_put(&cub->img, x++, y,
					((cub->textures.ceiling_rgb.r << 16)
						+ (cub->textures.ceiling_rgb.g << 8)
						+ (cub->textures.ceiling_rgb.b)));
		else
		{
			while (x < WINDOW_WIDTH)
				ft_mlx_pixel_put(&cub->img, x++, y,
					((cub->textures.floor_rgb.r << 16)
						+ (cub->textures.floor_rgb.g << 8)
						+ (cub->textures.floor_rgb.b)));
		}
		y++;
	}
}

void	render_3d(t_main *cub)
{
	int			x_screen;
	t_raycast	ray;
	t_vector	pos;
	double		camera_x;

	x_screen = 0;
	put_ceiling_floor(cub);
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
