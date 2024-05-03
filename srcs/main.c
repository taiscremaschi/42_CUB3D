/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/03 11:20:15 by tbolzan-         ###   ########.fr       */
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

int	end(t_main *main) //funcao para excluir e destroir todas imagens e janela
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

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	parsing_map(av, &main); //meu parsing 
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, ((main.larg) * 100), main.altura
			* 200, "cub3D"); //janela grande 
	image_inicialize(&main);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main); //fechar com esc
	mlx_hook(main.win, 33, 1L << 2, end, &main); // fechar com o x
	mlx_loop(main.mlx);
	return (0);
}
