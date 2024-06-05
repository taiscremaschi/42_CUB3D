/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:25 by paula             #+#    #+#             */
/*   Updated: 2024/06/05 14:48:26 by paula            ###   ########.fr       */
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
	if (ray->side == 1)
	{
		if (ray->ray_dir.dy > 0)
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

void	config_draw_color(t_main *cub, t_raycast *ray, t_draw_wall *wall, char c)
{
	if (c == 'c')
	{
		if (ray->hit_direction == 'S')
			wall->color = CLR_S;
		if (ray->hit_direction == 'N')
			wall->color = CLR_N;
		if (ray->hit_direction == 'W')
			wall->color = CLR_W;
		if (ray->hit_direction == 'E')
			wall->color = CLR_E;
	}
	else
	{
		if (ray->hit_direction == 'S')
			wall->text = cub->picture.p_south;
		if (ray->hit_direction == 'N')
			wall->text = cub->picture.p_north;
		if (ray->hit_direction == 'W')
			wall->text = cub->picture.p_west;
		if (ray->hit_direction == 'E')
			wall->text = cub->picture.p_east;
	}
}

void	draw_texture(t_raycast *ray, t_draw_wall *wall)
{
	ray->tex_x = (int)(wall->wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir.dx > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir.dy < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}

int		get_pixel(t_img *image, int x, int y)
{
	return (*(unsigned int *)(image->addr + (y * image->line_len + x
			* (image->bpp / 8))));
}

void	print_with_texture(t_raycast *ray, int x_screen, t_main *cub, t_draw_wall *wall)
{
	double	step = 1.0 * TEX_HEIGTH / ray->line_height;
	double tex_pos = (wall->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	int y = wall->draw_start;
	
	while(y < wall->draw_start)
	{
		ray->tex_y = (int)ray->tex_x & (TEX_HEIGTH - 1);
		tex_pos += step;
		wall->color = get_pixel(&wall->text, ray->tex_x, ray->tex_y);
		y++;
	}
}

void	draw_wall(t_raycast *ray, t_main *cub, int x_screen, t_vector pos)
{
	t_draw_wall	wall;

	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	wall.draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (wall.draw_start < 0)
		wall.draw_start = 0;
	wall.draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (wall.draw_end > WINDOW_HEIGHT)
		wall.draw_end = WINDOW_HEIGHT - 1;
	wall.wall_x = 0;
	if (ray->side == 0)
		wall.wall_x = pos.dy + ray->perp_wall_dist * ray->ray_dir.dy;
	else
		wall.wall_x = pos.dx + ray->perp_wall_dist * ray->ray_dir.dx;
	wall.wall_x -= floor((wall.wall_x));
	if (cub->show_texture == 0)
	{
		config_draw_color(cub, ray, &wall, 'c');
	//	print_wall(x_screen, cub, wall);
	}
	else
	{
		config_draw_color(cub, ray, &wall, 't');
		draw_texture(ray, &wall);
		print_with_texture(ray, x_screen, cub, &wall);
	}
	print_wall(x_screen, cub, wall);
}
