/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:15 by paula             #+#    #+#             */
/*   Updated: 2024/08/08 18:43:42 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	draw_line_to_frame(t_main *cub, t_vector start, t_vector end,
		int color)
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

void	print_wall(int x_screen, t_main *cub, t_draw_wall wall)
{
	t_vector	start;
	t_vector	end;

	start.dx = x_screen;
	start.dy = 0;
	end.dx = x_screen;
	end.dy = WINDOW_HEIGHT;
	start.dy = wall.draw_start;
	end.dy = wall.draw_end;
	draw_line_to_frame(cub, start, end, wall.color);
}

int	player_hit_2d(t_main *cub, t_vector dir, double pos_x, double pos_y)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	y = (int)floor(pos_y / MINI_WIDTH);
	x = (int)floor(pos_x / MINI_WIDTH);
	y1 = (int)floor((pos_y + (dir.dy)) / (MINI_WIDTH));
	x1 = (int)floor((pos_x + (dir.dx)) / (MINI_WIDTH));
	if (y1 < 0 || x1 < 0 || y > cub->height - 1)
		return (1);
	if ((cub->map[y1][x] == '1' || cub->map[y1][x] == '\0')
		&& ((cub->map[y][x1] == '1' || cub->map[y][x1] == '\0')))
		return (1);
	if ((cub->map[y1][x1] == '1' || cub->map[y1][x1] == '\0'))
		return (1);
	return (0);
}

static void	draw_pov(t_main *cub)
{
	t_vector	vision;
	t_vector	temp;
	t_vector	player;

	rotate2(cub->player.angle, &vision);
	temp.dx = cub->player.x;
	temp.dy = cub->player.y;
	player.dx = cub->player.x;
	player.dy = cub->player.y;
	while (!player_hit_2d(cub, vision, temp.dx, temp.dy))
	{
		temp.dx -= (1 * vision.dx);
		temp.dy -= (1 * vision.dy);
	}
	bresenham_line(cub, player, temp, 0xFF00FF);
}

void	draw_player(t_main *cub)
{
	t_vector	start;
	t_vector	rigth;
	t_vector	left;

	ft_mlx_pixel_put(&cub->img, cub->player.x, cub->player.y, 0xFF0000);
	start.dx = cub->player.x;
	start.dy = cub->player.y;
	rotate2(cub->player.angle + PI / 2, &rigth);
	rigth.dx = start.dx - rigth.dx * 10;
	rigth.dy = start.dy - rigth.dy * 10;
	rotate2(cub->player.angle - PI / 2, &left);
	left.dx = start.dx - left.dx * 10;
	left.dy = start.dy - left.dy * 10;
	draw_line_to_frame(cub, start, rigth, 0x0000FF);
	draw_line_to_frame(cub, start, left, 0x0000FF);
	draw_pov(cub);
}
