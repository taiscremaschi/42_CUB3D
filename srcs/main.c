/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/08 12:22:56 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

int	read_esc(int keycode, t_main *main)
{
	if (keycode == 65307)
		end(main);
	return (0);
}


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

void end_parsing(t_main *main)
{
	free_map(main->file_content);
	free(main->textures.ceiling_color);
	free(main->textures.south);
	free(main->textures.east);
	free(main->textures.west);
	free(main->textures.north);
	free(main->textures.floor_color);
}


int	end(t_main *main) //funcao para excluir e destroir todas imagens e janela
{
	free_map(main->file_content);
	mlx_destroy_image(main->mlx, main->picture.p_east);
	mlx_destroy_image(main->mlx, main->picture.p_west);
	mlx_destroy_image(main->mlx, main->picture.p_north);
	mlx_destroy_image(main->mlx, main->picture.p_south);
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
	parsing_map(av, &main); //meu parsing 
	main.mlx = mlx_init();
	main.win = mlx_new_window(main.mlx, ((100) * 100), main.height
			* 200, "cub3D"); //janela grande 
	image_inicialize(&main);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main);
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop(main.mlx);
	return (0);
}
