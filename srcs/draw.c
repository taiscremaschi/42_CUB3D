/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:27:31 by paula             #+#    #+#             */
/*   Updated: 2024/06/06 09:30:45 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	config_draw_color(t_main *cub, t_raycast *ray, t_draw_wall *wall,
		char c)
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

static void	draw_texture(t_raycast *ray, t_draw_wall *wall)
{
	ray->tex_x = (int)(wall->wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir.dx > 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir.dy < 0)
		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}

static void	print_with_texture(t_raycast *ray, int x_screen, t_main *cub,
		t_draw_wall *wall)
{
	int	tex_pos;
	int	color;

	color = 0;
	while (wall->draw_start < wall->draw_end)
	{
		tex_pos = wall->draw_start - (WINDOW_HEIGHT / 2) + (ray->line_height
				/ 2);
		ray->tex_y = ((tex_pos * TEX_HEIGTH) / ray->line_height);
		if (ray->tex_y <= -1 || ray->tex_x <= -1)
			return ;
		if (cub->map[ray->map.dy][ray->map.dx] == '1')
			color = get_pixel(&wall->text, ray->tex_x, ray->tex_y);
		ft_mlx_pixel_put(&cub->img, x_screen, wall->draw_start, color);
		wall->draw_start++;
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
		print_wall(x_screen, cub, wall);
	}
	else
	{
		config_draw_color(cub, ray, &wall, 't');
		draw_texture(ray, &wall);
		print_with_texture(ray, x_screen, cub, &wall);
	}
}
