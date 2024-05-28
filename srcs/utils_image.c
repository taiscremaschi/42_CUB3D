/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:15 by paula             #+#    #+#             */
/*   Updated: 2024/05/28 08:59:03 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	print_wall(int x_screen, t_main *cub, int draw_start, int draw_end)
{
	t_vector	start;
	t_vector	end;

	start.dx = x_screen;
	start.dy = 0;
	end.dx = x_screen;
	end.dy = WINDOW_HEIGHT;
	// draw_line2(cub, start, end, 0xFFFFFF);
	draw_line_to_frame(cub, start, end, 0xFFFFFF);
	start.dy = draw_start;
	end.dy = draw_end;
	// draw_line2(cub, start, end, ((cub->rgb.r << 16) + (cub->rgb.g << 8)
	// 		+ (cub->rgb.b)));
	draw_line_to_frame(cub, start, end, ((cub->rgb.r << 16) + (cub->rgb.g << 8)
			+ (cub->rgb.b)));
}

void	draw_line_to_frame(t_main *cub, t_vector start, t_vector end, int color)
{
	t_coord	del;
	double	pixels;

	del.x = end.dx - start.dx;
	del.y = end.dy - start.dy;
	pixels = sqrt((del.x * del.x) + (del.y * del.y));
	if (pixels > WINDOW_HEIGHT)
		pixels = WINDOW_HEIGHT;
	if (pixels < 0)
		pixels = 0;
	del.x /= pixels;
	del.y /= pixels;
	while (pixels > 0)
	{
		ft_mlx_pixel_put(&cub->img, start.dx, start.dy, color);
		start.dx += del.x;
		start.dy += del.y;
		--pixels;
	}
}

void	draw_line2(t_main *cub, t_vector start, t_vector end, int color)
{
	t_coord	del;
	double	pixels;

	del.x = end.dx - start.dx;
	del.y = end.dy - start.dy;
	pixels = sqrt((del.x * del.x) + (del.y * del.y));
	if (pixels > WINDOW_HEIGHT)
		pixels = WINDOW_HEIGHT;
	if (pixels < 0)
		pixels = 0;
	del.x /= pixels;
	del.y /= pixels;
	while (pixels > 0)
	{
		mlx_pixel_put(cub->mlx, cub->win, start.dx, start.dy, color);
		start.dx += del.x;
		start.dy += del.y;
		--pixels;
	}
}

static void	draw_pov(t_main *cub)
{
	t_vector	visao_cima;
	t_vector	visao_baixo;
	t_vector	temp;
	t_vector	player;

	rotate2(cub->player.angle + PI / 6, &visao_cima);
	rotate2(cub->player.angle - PI / 6, &visao_baixo);
	temp.dx = cub->player.x;
	temp.dy = cub->player.y;
	player.dx = cub->player.x;
	player.dy = cub->player.y;
	while (!player_hit(cub, visao_cima, temp.dx, temp.dy))
	{
		temp.dx -= visao_cima.dx;
		temp.dy -= visao_cima.dy;
	}
	draw_line_to_frame(cub, player, temp, 0xFF00FF);
	temp.dx = cub->player.x;
	temp.dy = cub->player.y;
	while (!player_hit(cub, visao_baixo, temp.dx, temp.dy))
	{
		temp.dx -= visao_baixo.dx;
		temp.dy -= visao_baixo.dy;
	}
	draw_line_to_frame(cub, player, temp, 0xFF00FF);
}

void	draw_player(t_main *cub)
{
	t_vector	start;
	t_vector	end;
	t_vector	rigth;
	t_vector	left;

	ft_mlx_pixel_put(&cub->img, cub->player.x, cub->player.y, 0xFF0000);
	start.dx = cub->player.x;
	start.dy = cub->player.y;
	end.dx = cub->player.x - cub->player.vector_front.dx * 15;
	end.dy = cub->player.y - cub->player.vector_front.dy * 15;
	rotate2(cub->player.angle + PI / 2, &rigth);
	rigth.dx = end.dx - rigth.dx * 10;
	rigth.dy = end.dy - rigth.dy * 10;
	rotate2(cub->player.angle - PI / 2, &left);
	left.dx = end.dx - left.dx * 10;
	left.dy = end.dy - left.dy * 10;
	draw_line_to_frame(cub, start, end, 0xFF0000);
	draw_line_to_frame(cub, end, rigth, 0x0000FF);
	draw_line_to_frame(cub, end, left, 0x0000FF);
	draw_pov(cub);
}

void	util_image(t_main *main, int x, int y)
{
	if (main->map[y][x] == '1')
		ft_mlx_put_image_frame(&main->img, (x * MINI_WIDTH), (y * MINI_WIDTH),
			&main->picture.wall);
	else if (main->map[y][x] != '\n' || main->map[y][x] == '0')
		ft_mlx_put_image_frame(&main->img, (x * MINI_WIDTH), (y * MINI_WIDTH),
			&main->picture.floor);
}
