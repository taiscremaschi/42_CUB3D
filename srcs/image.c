/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/13 16:15:10 by paula            ###   ########.fr       */
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
}

void	util_image(t_main *main, int x, int y)
{
	if (main->map[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.wall, (x
				* 20), (y * 20));
	else if (main->map[y][x] == 'P' || main->map[y][x] == '0')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.floor, (x
				* 20), (y * 20));
}
//************nao vamos usar pq é por angulos *************

int	render_image(t_main *main)
{
	int	x;
	int	y;

	y = -1;
	while (main->map[++y] != NULL)
	{
		x = -1;
		while (main->map[y][++x] != '\0')
			util_image(main, x, y);
	}
	mlx_put_image_to_window(main->mlx, main->win, main->picture.p_east,
		(main->player.x * 64), (main->player.y * 64));
	return (0);
}
// podemos utilizar algo disso mas vai ter que adaptar