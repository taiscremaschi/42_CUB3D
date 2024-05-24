/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:48:15 by paula             #+#    #+#             */
/*   Updated: 2024/05/24 09:17:44 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void draw_line2(t_main *cub, t_vector start, t_vector end, int color)
{
	// double del_x = x2 - x1;
	// double del_y = y2 - y1;
    t_coord del;
    double  pixels;

    del.x = end.dx - start.dx;
    del.y = end.dy - start.dy;
    pixels = sqrt((del.x * del.x) + (del.y * del.y));
	if (pixels > WINDOW_HEIGHT)
		pixels = WINDOW_HEIGHT;
	if(pixels < 0)
		pixels = 0;
	del.x /= pixels;
	del.y /= pixels;
	while (pixels > 0)
	{
		mlx_pixel_put(cub->mlx, cub->win, start.dx, start.dy, color);
		start.dx += del.x;
		start.dy += del.y;
		--pixels;
	}
}

void draw_player(t_main *cub)
{
    t_vector start;
    t_vector end;

    mlx_pixel_put(cub->mlx, cub->win, cub->player.x, cub->player.y, 0xFF0000);

    start.dx = cub->player.x;
    start.dy = cub->player.y;
    end.dx = cub->player.x - cub->player.vector_front.dx * 15;
    end.dy = cub->player.y - cub->player.vector_front.dy * 15;
    
    draw_line2(cub, start, end, 0xFF0000);


    // t_vector lado_cima, lado_baixo, visao_cima, visao_baixo;
    // rotate2(cub->player.angle+PI/2, &lado_cima);
    // rotate2(cub->player.angle-PI/2, &lado_baixo);
    // rotate2(cub->player.angle+PI/6, &visao_cima);
    // rotate2(cub->player.angle-PI/6, &visao_baixo);
    
    // draw_line2(cub, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, cub->player.x - cub->player.vector_front.dx*15 - lado_cima.dx*5, cub->player.y - cub->player.vector_front.dy*15 - lado_cima.dy*5, 0x0000FF);
    
    // draw_line2(cub, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, cub->player.x - cub->player.vector_front.dx*15 - lado_baixo.dx*5, cub->player.y - cub->player.vector_front.dy*15 - lado_baixo.dy*5, 0x0000FF);

    // double temp_x = cub->player.x;
    // double temp_y = cub->player.y;
    // while(!player_hit(cub, visao_cima, temp_x, temp_y))
    // {
    //     temp_x -= visao_cima.dx;
    //     temp_y -= visao_cima.dy;
    // }
    // draw_line2(cub, cub->player.x, cub->player.y, temp_x, temp_y, 0xFF00FF);
    // temp_x = cub->player.x;
    // temp_y = cub->player.y;
    // while(!player_hit(cub, visao_baixo, temp_x, temp_y))
    // {
    //     temp_x -= visao_baixo.dx;
    //     temp_y -= visao_baixo.dy;
    // }
    // draw_line2(cub, cub->player.x, cub->player.y, temp_x, temp_y, 0xFF00FF);
}

void	util_image(t_main *main, int x, int y)
{
	if (main->map[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.wall, (x
				* MINI_WIDTH), (y * MINI_WIDTH));
	else if (main->map[y][x] != '\n' || main->map[y][x] == '0')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.floor, (x
				* MINI_WIDTH), (y * MINI_WIDTH));
}
