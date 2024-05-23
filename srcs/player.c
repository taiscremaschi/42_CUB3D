/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:31:23 by paula             #+#    #+#             */
/*   Updated: 2024/05/23 09:34:02 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate2(double angle, t_vector *vector)
{
	vector->dx = cos(angle);
	vector->dy = sin(angle);
}

// proteger o PI, nao pode passar de 360
void	rotate_player(t_player *player, double dangle)
{
	double	perpendicular_angle;

	player->angle += dangle;
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
