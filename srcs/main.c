/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/05/20 21:24:03 by paula            ###   ########.fr       */
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
}

int	player_hit(t_main *cub, t_vector dir, double pos_x, double pos_y)
{
	int	y = (int)floor((pos_y + dir.dy)/ (MINI_WIDTH));
	int	x = (int)floor((pos_x + dir.dx)/ (MINI_WIDTH));
	printf("no HIT player x %d player y %d\n", x, y);

	if(y < 0 || x < 0 || y > cub->height - 1)
		return 1;
	if (cub->map[y][x] == '1' || cub->map[y][x] == '\0')
	{
		return 1;
	}
	printf("no HIT player x %d player y %d\n", x, y);
	return 0;

}

static void	simple_move(int key, t_main *cub)
{
	t_vector	dir;
	dir.dx = 0;
	dir.dy = 0;
	
	if (key == LEFT)
		rotate_player(&cub->player, -0.1);
	if (key == RIGHT)
		rotate_player(&cub->player, 0.1);
	if (key == W_UP)
	{
		dir.dy = cub->player.vector_front.dy * -1;
		dir.dx = cub->player.vector_front.dx * -1;
		if(!player_hit(cub,dir, cub->player.x, cub->player.y))
		{
			cub->player.y -= cub->player.vector_front.dy;// direction
			cub->player.x -= cub->player.vector_front.dx;
		}
	}
	if (key == S_DOWN)
	{
		dir.dy = cub->player.vector_front.dy * 1;
		dir.dx = cub->player.vector_front.dx * 1;
		if(!player_hit(cub,dir, cub->player.x, cub->player.y))
		{
			cub->player.y += cub->player.vector_front.dy;
			cub->player.x += cub->player.vector_front.dx;
		}
	}
	if (key == D_RIGHT)
	{
		dir.dy = cub->player.vector_perpendicular.dy * -1;
		dir.dx = cub->player.vector_perpendicular.dx * -1;
		if(!player_hit(cub,dir, cub->player.x, cub->player.y))
		{		
			cub->player.y -= cub->player.vector_perpendicular.dy; //camera
			cub->player.x -= cub->player.vector_perpendicular.dx;
		}
	}
	if (key == AA_LEFT)
	{
		dir.dy = cub->player.vector_perpendicular.dy * 1;
		dir.dx = cub->player.vector_perpendicular.dx * 1;
		if(!player_hit(cub,dir, cub->player.x, cub->player.y))
		{
			cub->player.y += cub->player.vector_perpendicular.dy;
			cub->player.x += cub->player.vector_perpendicular.dx;
		}
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
	player->x *= MINI_WIDTH + (MINI_WIDTH / 2);
	player->y *= MINI_WIDTH + (MINI_WIDTH / 2);
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
