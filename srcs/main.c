/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/14 15:13:20 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate(t_main *cub)
{
	cub->player.angle -= 0.1;
		printf("chamou %f\n", cub->player.angle);
	
	if(cub->player.angle < 0)
		cub->player.angle += 2 * PI;
	if (cub->player.angle > (2 * PI))
		cub->player.angle -= 2 * PI;
	cub->player.delta_x = cos(cub->player.angle * 5);
	cub->player.delta_y = sin(cub->player.angle * 5);
}

static void	simple_move(int key, t_main *cub)
{
	if(key == LEFT || key == RIGHT)
		rotate(cub);;
	if (key == W_UP)
		cub->player.y -= 1;
	if (key == S_DOWN)
		cub->player.y += 1;
	if (key == D_RIGHT)
		cub->player.x += 1;
	if (key == AA_LEFT)
		cub->player.x -= 1;

}

int	deal_key(int key, t_main *cub)
{
	//is_3d(key, cub);
	simple_move(key, cub);
	// ft_bzero(cub->img->addr, (WINDOW_HEIGHT * WINDOW_WIDTH
	// 		* sizeof(cub->img->bpp)));
	// draw_file(cub);
	// mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img->mlx_img, 0,
	// 	0);
	return (0);
}

void	init_img(t_main *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3D");
	if (cub->win == NULL)
	{
		free(cub->win);
		perror("error");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	parsing_map(av, &main);
	main.player.delta_x = cos(main.player.angle * 5);
	main.player.delta_y = sin(main.player.angle * 5);
	init_img(&main);
	image_inicialize(&main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main);
	mlx_key_hook(main.win, deal_key, &main);
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop_hook(main.mlx, render_image, &main);
	main.player.x *= 20;
	main.player.y *= 20;
	mlx_loop(main.mlx);
	return (0);
}
