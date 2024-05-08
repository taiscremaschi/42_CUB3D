/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/08 11:41:46 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"





int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	parsing_map(av, &main); //meu parsing 
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, ((100) * 100), main.height
			* 200, "cub3D"); //janela grande 
	image_inicialize(&main);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main); //fechar com esc
	mlx_hook(main.win, 33, 1L << 2, end, &main); // fechar com o x
	mlx_loop(main.mlx);
	return (0);
}
