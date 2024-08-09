/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:41:22 by paula             #+#    #+#             */
/*   Updated: 2024/08/09 09:16:56 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// direction
void	moves_up_down(int key, t_main *cub, t_vector dir)
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
void	moves_rl(int key, t_main *cub, t_vector dir)
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

void	moves(t_main *cub)
{
	t_vector	dir;

	dir.dx = 0;
	dir.dy = 0;
	if (cub->moves.press_l == 1 || cub->moves.press_q == 1)
		rotate_player(&cub->player, -0.1);
	else if (cub->moves.press_r == 1 || cub->moves.press_e == 1)
		rotate_player(&cub->player, 0.1);
	if (cub->moves.press_w == 1)
		moves_up_down(W_UP, cub, dir);
	if (cub->moves.press_s == 1)
		moves_up_down(S_DOWN, cub, dir);
	if (cub->moves.press_d == 1)
		moves_rl(D_RIGHT, cub, dir);
	if (cub->moves.press_a == 1)
		moves_up_down(AA_LEFT, cub, dir);
}

int	deal_key(int key, t_main *cub)
{
	if (key == W_UP)
		cub->moves.press_w = 1;
	if (key == D_RIGHT)
		cub->moves.press_d = 1;
	if (key == S_DOWN)
		cub->moves.press_s = 1;
	if (key == AA_LEFT)
		cub->moves.press_a = 1;
	if (key == RIGHT)
		cub->moves.press_r = 1;
	if (key == LEFT)
		cub->moves.press_l = 1;
	if (key == 'e')
		cub->moves.press_e = 1;
	if (key == 'q')
		cub->moves.press_q = 1;
	if (key == 'z')
		cub->moves.press_speed = 1;
	if (key == 65307)
		end(cub);
	return (0);
}

int	released_key(int key, t_main *cub)
{
	if (key == W_UP)
		cub->moves.press_w = 0;
	if (key == D_RIGHT)
		cub->moves.press_d = 0;
	if (key == S_DOWN)
		cub->moves.press_s = 0;
	if (key == AA_LEFT)
		cub->moves.press_a = 0;
	if (key == RIGHT)
		cub->moves.press_r = 0;
	if (key == LEFT)
		cub->moves.press_l = 0;
	if (key == 'e')
		cub->moves.press_e = 0;
	if (key == 'q')
		cub->moves.press_q = 0;
	if (key == 'z')
		cub->moves.press_speed = 0;
	ui_options(cub, key);
	return (0);
}
