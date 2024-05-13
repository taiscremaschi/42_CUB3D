/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/13 10:01:05 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	parsing_map(av, &main);
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, ((100) * 10), main.height * 20,
			"cub3D");
	image_inicialize(&main);
	mlx_put_image_to_window(main.mlx, main.win, main.img->mlx_img, 0,
		0);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main); 
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop(main.mlx);
	return (0);
}
