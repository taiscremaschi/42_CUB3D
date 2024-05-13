/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/13 15:36:46 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	simple_move(int key, t_main *cub)
{
	if (key == W_UP)
		cub->player.dir_y -= 1;
	else if (key == S_DOWN)
		cub->player.dir_y += 1;
	else if (key == D_RIGHT)
		cub->player.dir_x += 1;
	else if (key == AA_LEFT)
		cub->player.dir_x -= 1;
}

int	deal_key(int key, t_main *cub)
{
	//is_3d(key, cub);
	simple_move(key, cub);
	ft_bzero(cub->img->addr, (WINDOW_HEIGHT * WINDOW_WIDTH
			* sizeof(cub->img->bpp)));
	// draw_file(cub);
	// mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->mlx_img, 0,
	// 	0);
	return (0);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	parsing_map(av, &main);
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	image_inicialize(&main);
	mlx_loop_hook(main.mlx, render_image, &main);
	//mlx_key_hook(main.mlx, deal_key, &main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main);
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop(main.mlx);
	return (0);
}
