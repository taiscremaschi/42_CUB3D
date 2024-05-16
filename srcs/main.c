/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/16 20:32:08 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate2(double angle, t_vector *vector)
{
	vector->dx = cos(angle);
	vector->dy = sin(angle);
}

void	rotate_player(t_player *player, double dangle) //proteger o PI, nao pode passar de 360
{
	player->angle += dangle;
	rotate2(player->angle, &player->vector_front);
	double perpendicular_angle = player->angle + PI / 2;
		// significa rotacao 90 graus
	rotate2(perpendicular_angle, &player->vector_perpendicular);
	// if(cub->player.angle < 0)
	// 	cub->player.angle += 2 * PI;
	// else if (cub->player.angle > (2 * PI))
	// 	cub->player.angle -= 2 * PI;
	// cub->player.delta_x = cos(cub->player.angle * 5);
	// printf("del x eh %f\n", cub->player.delta_x);
	// cub->player.delta_y = sin(cub->player.angle * 5);
	// printf("del y eh %f\n", cub->player.delta_y);
}

static void	simple_move(int key, t_main *cub)
{
	if (key == LEFT)
		rotate_player(&cub->player, -0.1);
	if (key == RIGHT)
		rotate_player(&cub->player, 0.1);
	if (key == W_UP)
	{
		cub->player.y -= cub->player.vector_front.dy;// direction
		cub->player.x -= cub->player.vector_front.dx;
	}
	if (key == S_DOWN)
	{
		cub->player.y += cub->player.vector_front.dy;
		cub->player.x += cub->player.vector_front.dx;
	}
	if (key == D_RIGHT)
	{
		cub->player.y -= cub->player.vector_perpendicular.dy; //camera
		cub->player.x -= cub->player.vector_perpendicular.dx;
	}
	if (key == AA_LEFT)
	{
		cub->player.y += cub->player.vector_perpendicular.dy;
		cub->player.x += cub->player.vector_perpendicular.dx;
	}
}

static void	is_minimap(int key, t_main *cub)
{
	if (key == 112 && cub->is_mini == 0)
	{
		cub->is_mini = 1;
	}
	else if (key == 112 && cub->is_mini != 0)
		cub->is_mini = 0;
}

int	deal_key(int key, t_main *cub)
{
	is_minimap(key, cub);
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
	cub->win = mlx_new_window(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (cub->win == NULL)
	{
		free(cub->win);
		perror("error");
		exit(EXIT_FAILURE);
	}
}

double	define_angle(char position, float *angle)
{
	if (position == 'N')
		*angle = PI / 2;
	else if (position == 'E') //ISSO DEVERIA SER NO W, OQ ACONTECEU????
		*angle = PI;
	else if (position == 'S')
		*angle = 3 * PI / 2;
	else
		*angle = 0;
	return (*angle);
}

void	config_player(t_player *player)
{
	float	angle;

	angle = define_angle(player->position, &angle);
	rotate_player(player, angle);
	player->x *= MINI_WIDTH;
	player->y *= MINI_WIDTH;
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	main.is_mini = 0;
	parsing_map(av, &main);
	config_player(&main.player);
	init_img(&main);
	image_inicialize(&main);
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main);
	mlx_key_hook(main.win, deal_key, &main);
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_loop(main.mlx);
	return (0);
}
