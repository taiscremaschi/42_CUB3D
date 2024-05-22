/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:25 by paula             #+#    #+#             */
/*   Updated: 2024/05/22 11:04:42 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	start_ray(t_raycast *ray, double cameraX, t_main *cub, t_vector pos)
{
	t_vector	*dir;
	t_vector	*plan;

	dir = &cub->player.vector_front;
	plan = &cub->player.vector_perpendicular;
	pos.dx = cub->player.x / MINI_WIDTH;
	pos.dy = cub->player.y / MINI_WIDTH;
	ray->rayDir.dx = dir->dx + plan->dx * cameraX;
	ray->rayDir.dy = dir->dy + plan->dy * cameraX;
	ray->map.dx = (int)pos.dx;
	ray->map.dy = (int)pos.dy;
	ray->deltaDist.dx = fabs(1 / ray->rayDir.dx);
	ray->deltaDist.dy = fabs(1 / ray->rayDir.dy);
}

void	ray_steps(t_raycast *ray, t_vector pos)
{
	if (ray->rayDir.dx < 0)
	{
		ray->step.dx = -1;
		ray->sideDist.dx = (pos.dx - ray->map.dx) * ray->deltaDist.dx;
	}
	else
	{
		ray->step.dx = 1;
		ray->sideDist.dx = (ray->map.dx + 1 - pos.dx) * ray->deltaDist.dx;
	}
	if (ray->rayDir.dy < 0)
	{
		ray->step.dy = -1;
		ray->sideDist.dy = (pos.dy - ray->map.dy) * ray->deltaDist.dy;
	}
	else
	{
		ray->step.dy = 1;
		ray->sideDist.dy = (ray->map.dy + 1 - pos.dy) * ray->deltaDist.dy;
	}
}

void	performing_dda(t_raycast *ray, t_main *cub)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist.dx < ray->sideDist.dy)
		{
			ray->sideDist.dx += ray->deltaDist.dx;
			ray->map.dx += ray->step.dx;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.dy += ray->deltaDist.dy;
			ray->map.dy += ray->step.dy;
			ray->side = 1;
		}
		if (cub->map[ray->map.dy][ray->map.dx] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDist.dx - ray->deltaDist.dx);
	else
		ray->perpWallDist = (ray->sideDist.dy - ray->deltaDist.dy);
}
