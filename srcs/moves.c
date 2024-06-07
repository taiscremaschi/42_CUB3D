/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:41:22 by paula             #+#    #+#             */
/*   Updated: 2024/06/07 17:06:03 by paula            ###   ########.fr       */
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

int	deal_key(int key, t_main *cub)
{
	t_vector	dir;

	if (key == 65307)
		end(cub);
	dir.dx = 0;
	dir.dy = 0;
	if (key == LEFT || key == 'q')
		rotate_player(&cub->player, -0.1);
	else if (key == RIGHT || key == 'e')
		rotate_player(&cub->player, 0.1);
	else if (key == W_UP || key == S_DOWN)
		moves_up_down(key, cub, dir);
	else if (key == D_RIGHT || key == AA_LEFT)
		moves_rl(key, cub, dir);
	return (0);
}

int	released_key(int key, t_main *cub)
{
	t_vector	dir;

	dir.dx = 0;
	dir.dy = 0;
	if (!cub->show_texture && key == 't')
		cub->show_texture = 1;
	else if (cub->show_texture && key == 'c')
		cub->show_texture = 0;
	else if (key == LEFT || key == 'q')
		rotate_player(&cub->player, -0.1);
	else if (key == RIGHT || key == 'e')
		rotate_player(&cub->player, 0.1);
	else if (key == W_UP || key == S_DOWN)
		moves_up_down(key, cub, dir);
	else if (key == D_RIGHT || key == AA_LEFT)
		moves_rl(key, cub, dir);
	else if (key == '2')
		cub->is_mini = 1;
	else if (key == '3')
		cub->is_mini = 0;
	return (0);
}
