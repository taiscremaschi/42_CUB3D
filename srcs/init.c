/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:58:18 by paula             #+#    #+#             */
/*   Updated: 2024/06/06 15:43:31 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	init_img_clean(t_main *cub)
{
	cub->picture.clean.mlx_img = mlx_new_image(cub->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	cub->picture.clean.addr = mlx_get_data_addr(cub->picture.clean.mlx_img,
			&cub->picture.clean.bpp, &cub->picture.clean.line_len,
			&cub->picture.clean.endian);
	cub->picture.clean.width = WINDOW_WIDTH;
	cub->picture.clean.height = WINDOW_HEIGHT;
}

static void	init_img(t_main *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (cub->win == NULL)
	{
		free(cub->win);
		perror("error");
		exit(EXIT_FAILURE);
	}
	cub->img.mlx_img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.mlx_img, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	cub->img.width = WINDOW_WIDTH;
	cub->img.height = WINDOW_HEIGHT;
	init_img_clean(cub);
	cub->is_mini = 0;
	cub->show_texture = 1;
}

void	init_everything(t_main *cub)
{
	cub->player.angle = 0;
	cub->player.vector_front.dx = 0;
	cub->player.vector_front.dy = 0;
	cub->player.vector_perpendicular.dx = 0;
	cub->player.vector_perpendicular.dy = 0;
	init_img(cub);
}
