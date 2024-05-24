/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:25 by paula             #+#    #+#             */
/*   Updated: 2024/05/24 09:19:46 by paula            ###   ########.fr       */
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
	ray->rayDir.dx = -dir->dx - plan->dx * cameraX;
	ray->rayDir.dy = -dir->dy - plan->dy * cameraX;
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
		ray->sideDist.dx = (ray->map.dx + 1.0 - pos.dx) * ray->deltaDist.dx;
	}
	if (ray->rayDir.dy < 0)
	{
		ray->step.dy = -1;
		ray->sideDist.dy = (pos.dy - ray->map.dy) * ray->deltaDist.dy;
	}
	else
	{
		ray->step.dy = 1;
		ray->sideDist.dy = (ray->map.dy + 1.0 - pos.dy) * ray->deltaDist.dy;
	}
}

// verificar
static void	save_direction(t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->rayDir.dx > 0)
			ray->hit_direction = 'W';
		else
			ray->hit_direction = 'E';
	}
	else
	{
		if (ray->rayDir.dx > 0)
			ray->hit_direction = 'N';
		else
			ray->hit_direction = 'S';
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
	if (cub->map[ray->map.dy][ray->map.dx] == '1')
		save_direction(ray);
}

void	draw_wall(t_raycast *ray, t_main *cub, int x_screen, t_vector pos)
{
	int		drawStart;
	int		drawEnd;
	double	wall_x;

	ray->lineHeight = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	drawStart = -ray->lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = ray->lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (drawEnd > WINDOW_HEIGHT)
		drawEnd = WINDOW_HEIGHT - 1;
	wall_x = 0;
	if (ray->side == 0)
		wall_x = pos.dy + ray->perpWallDist * ray->rayDir.dy;
	else
		wall_x = pos.dx + ray->perpWallDist * ray->rayDir.dx;
	wall_x -= floor((wall_x));
	if (cub->map[ray->map.dy][ray->map.dx] == 1)
	{
		cub->rgb.r = 0;
		cub->rgb.g = 0;
		cub->rgb.b = 255;
	}
	if (ray->side == 1)
	{
		cub->rgb.r = 125;
		cub->rgb.g = 0;
		cub->rgb.b = 0;
		// if(hit_direction == 'S')
		// {
		// 	cub->rgb.r = 255;
		// 	cub->rgb.g = 0;
		// 	cub->rgb.b = 0;
		// }
		// if(hit_direction == 'N')
		// {
		// 	cub->rgb.r = 0;
		// 	cub->rgb.g = 255;
		// 	cub->rgb.b = 0;
		// }
		// if(hit_direction == 'E')
		// {
		// 	cub->rgb.r = 0;
		// 	cub->rgb.g = 0;
		// 	cub->rgb.b = 10;
		// }
		// if(hit_direction == 'W')
		// {
		// 	cub->rgb.r = 0;
		// 	cub->rgb.g = 0;
		// 	cub->rgb.b = 120;
		// }
	}
	// pintar de branco antes eh apenas uma solucao temporaria..preciso trabalhar com imagens
	// draw_line2(cub, x_screen, 0, x_screen, WINDOW_HEIGHT, 0xFFFFFF);
	// draw_line2(cub, x_screen, drawStart, x_screen, drawEnd, ((cub->rgb.r << 16)
	// 		+ (cub->rgb.g << 8) + (cub->rgb.b)));
}
