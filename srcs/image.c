/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/14 11:48:01 by paula            ###   ########.fr       */
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

void draw_player(t_main *cub)
{
	static int x=-1;
	static int y=-1;

	//ft_mlx_pixel_put(cub->map, cub->player.x, cub->player.y, 0xFFFFFF);
	if (cub->player.x != x || cub->player.y != y){
		//mlx_put_image_to_window(cub->mlx, cub->win, cub->picture.p_north, cub->player.x, cub->player.y);
		mlx_pixel_put(cub->mlx, cub->win, cub->player.x, cub->player.y, 0xFF0000);
		
		x = cub->player.x;
		y = cub->player.y;
	}
}

void	util_image(t_main *main, int x, int y)
{
	if (main->map[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.wall, (x
				* 20), (y * 20));
	// else if (main->map[y][x] != '\n' || main->map[y][x] == '0')
	// 	mlx_put_image_to_window(main->mlx, main->win, main->picture.floor, (x
	// 			* 20), (y * 20));
	
}
//************nao vamos usar pq é por angulos *************

int	render_image(t_main *main)
{
	static int d = 0;
	int	x;
	int	y;

	y = -1;
	while (main->map[++y] != NULL && d == 0)
	{
		x = -1;
		while (main->map[y][++x] != '\0')
			util_image(main, x, y);
	}
	d = 0;
	draw_player(main);
	return (0);
}
// podemos utilizar algo disso mas vai ter que adaptar