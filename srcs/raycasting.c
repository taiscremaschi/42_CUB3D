/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:25 by paula             #+#    #+#             */
/*   Updated: 2024/05/24 10:13:16 by paula            ###   ########.fr       */
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
	ray->ray_dir.dx = -dir->dx - plan->dx * cameraX;
	ray->ray_dir.dy = -dir->dy - plan->dy * cameraX;
	ray->map.dx = (int)pos.dx;
	ray->map.dy = (int)pos.dy;
	ray->delta_dist.dx = fabs(1 / ray->ray_dir.dx);
	ray->delta_dist.dy = fabs(1 / ray->ray_dir.dy);
}

void	ray_steps(t_raycast *ray, t_vector pos)
{
	if (ray->ray_dir.dx < 0)
	{
		ray->step.dx = -1;
		ray->side_dist.dx = (pos.dx - ray->map.dx) * ray->delta_dist.dx;
	}
	else
	{
		ray->step.dx = 1;
		ray->side_dist.dx = (ray->map.dx + 1.0 - pos.dx) * ray->delta_dist.dx;
	}
	if (ray->ray_dir.dy < 0)
	{
		ray->step.dy = -1;
		ray->side_dist.dy = (pos.dy - ray->map.dy) * ray->delta_dist.dy;
	}
	else
	{
		ray->step.dy = 1;
		ray->side_dist.dy = (ray->map.dy + 1.0 - pos.dy) * ray->delta_dist.dy;
	}
}

// verificar
static void	save_direction(t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir.dx > 0)
			ray->hit_direction = 'W';
		else
			ray->hit_direction = 'E';
	}
	else
	{
		if (ray->ray_dir.dx > 0)
			ray->hit_direction = 'N';
		else
			ray->hit_direction = 'S';
	}
}

void	performing_dda(t_raycast *ray, t_main *cub)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.dx < ray->side_dist.dy)
		{
			ray->side_dist.dx += ray->delta_dist.dx;
			ray->map.dx += ray->step.dx;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.dy += ray->delta_dist.dy;
			ray->map.dy += ray->step.dy;
			ray->side = 1;
		}
		if (cub->map[ray->map.dy][ray->map.dx] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.dx - ray->delta_dist.dx);
	else
		ray->perp_wall_dist = (ray->side_dist.dy - ray->delta_dist.dy);
	if (cub->map[ray->map.dy][ray->map.dx] == '1')
		save_direction(ray);
}

// if (cub->map[ray->map.dy][ray->map.dx] == 1)
// {
// 	cub->rgb.r = 0;
// 	cub->rgb.g = 0;
// 	cub->rgb.b = 255;
// }
void	draw_wall(t_raycast *ray, t_main *cub, int x_screen, t_vector pos)
{
	int		draw_start;
	int		draw_end;
	double	wall_x;

	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end > WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	wall_x = 0;
	if (ray->side == 0)
		wall_x = pos.dy + ray->perp_wall_dist * ray->ray_dir.dy;
	else
		wall_x = pos.dx + ray->perp_wall_dist * ray->ray_dir.dx;
	wall_x -= floor((wall_x));
	if (ray->side == 1)
	{
		cub->rgb.r = 125;
		cub->rgb.g = 0;
		cub->rgb.b = 0;
	}
	print_wall(x_screen, cub, draw_start, draw_end);
}
