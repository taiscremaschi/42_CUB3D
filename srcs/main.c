/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/02 15:57:47 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	free_map(char **m)
{
	int	i;

	i = 0;
	while (m[i])
	{
		free(m[i]);
		i++;
	}
	free(m);
}

int	end(t_main *main)
{
	free_map(main->map);
	mlx_destroy_image(main->mlx, main->picture.collectable);
	mlx_destroy_image(main->mlx, main->picture.wall);
	mlx_destroy_image(main->mlx, main->picture.floor);
	mlx_destroy_image(main->mlx, main->picture.exit);
	mlx_destroy_image(main->mlx, main->picture.player);
	mlx_destroy_window(main->mlx, main->win);
	mlx_destroy_display(main->mlx);
	mlx_loop_end(main->mlx);
	free(main->mlx);
	exit(0);
}

//line 53: janela; line 56: esc and line 57: close x
int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	check_map(av, &main);
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, ((main.larg) * 100), main.altura
			* 200, "cub3D");
	image_inicialize(&main);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main);
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop(main.mlx);
	return (0);
}