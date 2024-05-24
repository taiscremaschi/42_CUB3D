/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:41:22 by paula             #+#    #+#             */
/*   Updated: 2024/05/23 09:58:27 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// direction
static void	moves_up_down(int key, t_main *cub, t_vector dir)
{
	if (key == W_UP)
	{
		dir.dy = cub->player.vector_front.dy * -1;
		dir.dx = cub->player.vector_front.dx * -1;
		if (!player_hit(cub, dir, cub->player.x, cub->player.y))
		{
			cub->player.y -= cub->player.vector_front.dy;
			cub->player.x -= cub->player.vector_front.dx;
		}
	}
	if (key == S_DOWN)
	{
		dir.dy = cub->player.vector_front.dy * 1;
		dir.dx = cub->player.vector_front.dx * 1;
		if (!player_hit(cub, dir, cub->player.x, cub->player.y))
		{
			cub->player.y += cub->player.vector_front.dy;
			cub->player.x += cub->player.vector_front.dx;
		}
	}
}

// camera
static void	moves_rl(int key, t_main *cub, t_vector dir)
{
	if (key == D_RIGHT)
	{
		dir.dy = cub->player.vector_perpendicular.dy * -1;
		dir.dx = cub->player.vector_perpendicular.dx * -1;
		if (!player_hit(cub, dir, cub->player.x, cub->player.y))
		{
			cub->player.y -= cub->player.vector_perpendicular.dy;
			cub->player.x -= cub->player.vector_perpendicular.dx;
		}
	}
	if (key == AA_LEFT)
	{
		dir.dy = cub->player.vector_perpendicular.dy * 1;
		dir.dx = cub->player.vector_perpendicular.dx * 1;
		if (!player_hit(cub, dir, cub->player.x, cub->player.y))
		{
			cub->player.y += cub->player.vector_perpendicular.dy;
			cub->player.x += cub->player.vector_perpendicular.dx;
		}
	}
}

static void	simple_move(int key, t_main *cub)
{
	t_vector	dir;

	dir.dx = 0;
	dir.dy = 0;
	if (key == LEFT)
		rotate_player(&cub->player, -0.1);
	if (key == RIGHT)
		rotate_player(&cub->player, 0.1);
	if (key == W_UP || key == S_DOWN)
		moves_up_down(key, cub, dir);
	if (key == D_RIGHT || key == AA_LEFT)
		moves_rl(key, cub, dir);
}

static void	is_minimap(int key, t_main *cub)
{
	if (key == '2')
	{
		cub->is_mini = 1;
	}
	else if (key == '3')
		cub->is_mini = 0;
}

// ft_bzero(cub->img->addr, (WINDOW_HEIGHT * WINDOW_WIDTH
// 		* sizeof(cub->img->bpp)));
// draw_file(cub);
// mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->mlx_img, 0,
// 	0);
int	deal_key(int key, t_main *cub)
{
	is_minimap(key, cub);
	simple_move(key, cub);
	return (0);
}
