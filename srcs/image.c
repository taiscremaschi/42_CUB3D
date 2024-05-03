/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/05/03 12:20:55 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	image_inicialize(t_main *main)
{
	int	i;

	main->picture.collectable = mlx_xpm_file_to_image(main->mlx,
			"./images/coletavel.xpm", &i, &i);
	main->picture.wall = mlx_xpm_file_to_image(main->mlx, "./images/wall.xpm",
			&i, &i);
	main->picture.player = mlx_xpm_file_to_image(main->mlx,
			"./images/player.xpm", &i, &i);
	main->picture.floor = mlx_xpm_file_to_image(main->mlx, "./images/chao.xpm",
			&i, &i);
	main->picture.exit = mlx_xpm_file_to_image(main->mlx, "./images/exit.xpm",
			&i, &i);
}

void	util_image(t_main *main, int x, int y)
{
	if (main->file_content[y][x] == '1')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.wall, (x
				* 64), (y * 64));
	else if (main->file_content[y][x] == 'P' || main->file_content[y][x] == '0')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.floor, (x
				* 64), (y * 64));
	else if (main->file_content[y][x] == 'E')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.exit, (x
				* 64), (y * 64));
	else if (main->file_content[y][x] == 'C')
		mlx_put_image_to_window(main->mlx, main->win, main->picture.collectable,
			(x * 64), (y * 64));
}

int	render_image(t_main *main)
{
	int	x;
	int	y;

	y = -1;
	while (main->file_content[++y] != NULL)
	{
		x = -1;
		while (main->file_content[y][++x] != '\0')
			util_image(main, x, y);
	}
	mlx_put_image_to_window(main->mlx, main->win, main->picture.player,
		(main->player.x * 64), (main->player.y * 64));
	return (0);
}
