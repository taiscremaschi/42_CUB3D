/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:31:23 by paula             #+#    #+#             */
/*   Updated: 2024/06/06 10:12:48 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// EXTRA_STEP to check the hit if the player wants to take another step
int	player_hit(t_main *cub, t_vector dir, double pos_x, double pos_y)
{
	int	x;
	int	y;

	y = (int)floor((pos_y + (dir.dy * EXTRA_STEP)) / (MINI_WIDTH));
	x = (int)floor((pos_x + (dir.dx * EXTRA_STEP)) / (MINI_WIDTH));
	if (y < 0 || x < 0 || y > cub->height - 1)
		return (1);
	if (cub->map[y][x] == '1' || cub->map[y][x] == '\0')
		return (1);
	return (0);
}

void	rotate2(double angle, t_vector *vector)
{
	vector->dx = cos(angle);
	vector->dy = sin(angle);
}

// protected angle from double overflow
void	rotate_player(t_player *player, double dangle)
{
	double	perpendicular_angle;

	player->angle += dangle;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->angle > (2 * PI))
		player->angle -= 2 * PI;
	rotate2(player->angle, &player->vector_front);
	perpendicular_angle = player->angle + PI / 2;
	rotate2(perpendicular_angle, &player->vector_perpendicular);
}

static double	define_angle(char position, float *angle)
{
	if (position == 'N')
		*angle = PI / 2;
	else if (position == 'E')
		*angle = PI;
	else if (position == 'S')
		*angle = 3 * PI / 2;
	else
		*angle = 0;
	return (*angle);
}

void	config_player(t_player *player)
{
	float	angle;

	angle = define_angle(player->position, &angle);
	rotate_player(player, angle);
	player->x = (player->x * MINI_WIDTH) + (MINI_WIDTH / 2);
	player->y = (player->y * MINI_WIDTH) + (MINI_WIDTH / 2);
}
