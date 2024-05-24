/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:41:20 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/14 08:41:16 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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

// funcao para excluir e destroir todas imagens e janela
int	end(t_main *main)
{
	free_map(main->map);
	mlx_destroy_image(main->mlx, main->picture.p_east);
	mlx_destroy_image(main->mlx, main->picture.p_west);
	mlx_destroy_image(main->mlx, main->picture.p_north);
	mlx_destroy_image(main->mlx, main->picture.p_south);
	mlx_destroy_window(main->mlx, main->win);
	free(main->img);
	mlx_destroy_display(main->mlx);
	mlx_loop_end(main->mlx);
	free(main->textures.ceiling_color);
	free(main->textures.south);
	free(main->textures.east);
	free(main->textures.west);
	free(main->textures.north);
	free(main->textures.floor_color);
	free(main->mlx);
	exit(0);
}
