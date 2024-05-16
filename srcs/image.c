/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/16 21:19:48 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	image_inicialize(t_main *main)
{
	int	i;

	main->picture.p_north = mlx_xpm_file_to_image(main->mlx,
			main->textures.north, &i, &i);
	main->picture.p_south = mlx_xpm_file_to_image(main->mlx,
			main->textures.south, &i, &i);
	main->picture.p_west = mlx_xpm_file_to_image(main->mlx, main->textures.west,
			&i, &i);
	main->picture.p_east = mlx_xpm_file_to_image(main->mlx, main->textures.east,
			&i, &i);
	main->picture.floor = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/floor.xpm",
			&i, &i);
	main->picture.wall = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/test.xpm",
			&i, &i);
	main->picture.player2d = mlx_xpm_file_to_image(main->mlx, "./images/player2d_2.xpm" , &i, &i);
	// main->img->mlx_img = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/floor.xpm",
	// 		main->img->width, main->img->height);
	// main->img->addr = mlx_get_data_addr(main->img->mlx_img, &(main->img->bpp), &(main->img->line_len),
	// 		&(main->img->endian));
	// main->picture.wall = mlx_xpm_file_to_image(main->mlx, "./texture/map2d/test.xpm",
	// 		&i, &i);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (y >= 0 && x >= 0 && y < WINDOW_HEIGHT && x < WINDOW_WIDTH)
	{
		dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dest = color;
	}
}

void draw_line2(t_main *cub, double x1, double y1, double x2, double y2, int color){
	double del_x = x2 - x1;
	double del_y = y2 - y1;
	
	int pixels = sqrt((del_x * del_x) + (del_y * del_y));
	
	del_x /= pixels;
	del_y /= pixels;

	while (pixels)
	{
		mlx_pixel_put(cub->mlx, cub->win, x1, y1, color);
		x1 += del_x;
		y1 += del_y;
		--pixels;
	}
}

void	draw_line(t_main *cub)
{
	double del_x = 20 - cub->player.x;
	double del_y = 20 - cub->player.y;
	int pixels = sqrt((del_x * del_x) + (del_y * del_y));
	del_x /= pixels;
	del_y /= pixels;
	double pixelX = cub->player.x;
	double pixelY = cub->player.y;
	while (pixels)
	{
		mlx_pixel_put(cub->mlx, cub->win, pixelX, pixelY, 0xFFFFFF);
		pixelX += del_x;
		pixelY += del_y;
		--pixels;
	}
}

// void	drawRays(t_player *player, t_main *cub)
// {
// 	float	ra = player->angle;
// 	int	r, dof, mx, my, mp;
// 	float	ry, rx, yo, xo;

// 	for(r = 0; r < 1; r++)
// 	{
// 		dof = 0;
// 		float aTan = -1 / tan(ra);
// 		if(ra < PI) //looking up
// 		{
// 			printf("DOWN %f\n", ra);
// 			ry = (((int)player->y >> 6) << 6) - 0.0001;
// 			rx = (player->y - ry) * aTan + player->x;
// 			yo = MINI_WIDTH;
// 			xo = -yo * aTan;
// 		}
// 		if(ra > PI) //looking down
// 		{
// 			printf("UP %f\n", ra);
// 			ry = (((int)player->y >> 6) << 6) + 64;
// 			rx = (player->y - ry) * aTan + player->x;
// 			yo = -64;
// 			xo = -yo * aTan;
// 		}
// 		if(ra == 0) //looking left or rigth
// 		{
// 			printf("RIGHT %f\n", ra);
// 			ry = player->y;
// 			rx = player->x;
// 			yo = 0;
// 			xo = 64;
// 		}
// 		if(ra == PI) //looking left or rigth
// 		{
// 			printf("LEFT %f\n", ra);
// 			ry = player->y;
// 			rx = player->x;
// 			yo = 0;
// 			xo = 64;
// 		}
		
// 		int help = 0;
// 		mx = (int)(rx)>>6;
// 		my = (int)(ry)>>6;

// 		if (!(help++))
// 			printf("mx %d my %d rx %f ry %f xo %f yo %f\n", mx, my, rx, ry, xo, yo);
// 		// while(dof < 20)
// 		// {

// 	//		 mp = my*MINI_WIDTH + mx;
// 			if(mx < 0 && my < 0 && mx > 6 && my > 6 && cub->map[mx][my] != '1')
// 			{
// 				rx +=xo;
// 				ry +=yo;
// 			}
// 	//	}
// 		draw_line2(cub, cub->player.x, cub->player.y, rx, ry, 0x00FFFF);
// 	}
// }

void draw_player(t_main *cub)
{
		mlx_pixel_put(cub->mlx, cub->win, cub->player.x, cub->player.y, 0xFF0000);

		draw_line2(cub, cub->player.x, cub->player.y, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, 0xFF0000);


		t_vector lado_cima, lado_baixo, visao_cima, visao_baixo;
		rotate2(cub->player.angle+PI/2, &lado_cima);
		rotate2(cub->player.angle-PI/2, &lado_baixo);
		rotate2(cub->player.angle+PI/6, &visao_cima);
		rotate2(cub->player.angle-PI/6, &visao_baixo);
		
		draw_line2(cub, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, cub->player.x - cub->player.vector_front.dx*15 - lado_cima.dx*5, cub->player.y - cub->player.vector_front.dy*15 - lado_cima.dy*5, 0x0000FF);
		
		draw_line2(cub, cub->player.x - cub->player.vector_front.dx*15, cub->player.y - cub->player.vector_front.dy*15, cub->player.x - cub->player.vector_front.dx*15 - lado_baixo.dx*5, cub->player.y - cub->player.vector_front.dy*15 - lado_baixo.dy*5, 0x0000FF);

		//drawRays(&cub->player, cub);

		draw_line2(cub, cub->player.x, cub->player.y, cub->player.x - visao_cima.dx*20, cub->player.y - visao_cima.dy*20, 0xFF00FF);
		
		draw_line2(cub, cub->player.x, cub->player.y, cub->player.x - visao_baixo.dx*20, cub->player.y - visao_baixo.dy*20, 0xFF00FF);

		
	//}
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
//************nao vamos usar pq é por angulos *************

void	render_mini(t_main *cub)
{
	static int d = 0;
	int	x;
	int	y;

	y = -1;
	while (cub->map[++y] != NULL && d == 0)
	{
		x = -1;
		while (cub->map[y][++x] != '\0')
			util_image(cub, x, y);
	}
	d = 0;
	draw_player(cub);
}

void	render_3D(t_main *cub)
{
	int x_screen;
	double w;
	t_vector	*dir = &cub->player.vector_front;
	t_vector	*plan = &cub->player.vector_perpendicular;

	x_screen = 0;
	w = WINDOW_WIDTH;
	while(x_screen < w)
	{
		double cameraX = 2 * (x_screen / w) - 1;
		double rayDirx = dir->dx + plan->dx * cameraX;
		double rayDiry = dir->dy + plan->dy * cameraX;

		int mapx = (int)cub->player.x / MINI_WIDTH; //vou precisar criar a var posicao pq no minimap eu multipliquei
		int mapy = (int)cub->player.y / MINI_WIDTH;
		
		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirx == 0) ? 1e30 : fabs(1 / rayDirx);
		double deltaDistY = (rayDiry == 0) ? 1e30 : fabs(1 / rayDiry);
		double perWallDist;
		
		int stepX;
		int stepY;

		int hit = 0;
		int side //NS or EW
		
		
		x_screen++;
	}
}

int	render_image(t_main *main)
{
	if(main->is_mini)
		render_mini(main);
	else
		render_3D(main);
	return 0;	
}
// podemos utilizar algo disso mas vai ter que adaptar