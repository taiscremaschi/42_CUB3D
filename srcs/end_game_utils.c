/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:41:20 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/08/09 12:27:47 by paula            ###   ########.fr       */
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
	my_mlx_destroy_image(main->mlx, main->picture.floor2d.mlx_img);
	my_mlx_destroy_image(main->mlx, main->picture.wall2d.mlx_img);
	my_mlx_destroy_image(main->mlx, main->picture.clean.mlx_img);
	my_mlx_destroy_image(main->mlx, main->img.mlx_img);
	my_mlx_destroy_image(main->mlx, main->picture.p_east.mlx_img);
	my_mlx_destroy_image(main->mlx, main->picture.p_west.mlx_img);
	my_mlx_destroy_image(main->mlx, main->picture.p_north.mlx_img);
	my_mlx_destroy_image(main->mlx, main->picture.p_south.mlx_img);
	mlx_destroy_window(main->mlx, main->win);
	mlx_destroy_display(main->mlx);
	mlx_loop_end(main->mlx);
	free(main->path.ceiling_color);
	free(main->path.south);
	free(main->path.east);
	free(main->path.west);
	free(main->path.north);
	free(main->path.floor_color);
	free(main->mlx);
	exit(0);
}

void	my_mlx_destroy_image(void *mlx_ptr, void *img_ptr)
{
	if (img_ptr != NULL)
		mlx_destroy_image(mlx_ptr, img_ptr);
}
