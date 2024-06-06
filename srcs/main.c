/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/06/06 09:23:55 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_instruction(void)
{
	ft_printf(BLUE "╔═══════════════════════════════════════════"
		"═════════╗"
		RESET "\n" MARGENTA " "
		"                CONTROLS INFORMATION:" "\n"
		"    Press '2' to 2D and 3 to 3D"
		"\n" "    Press 't' to textures and 'c' to colors" BLUE "\n"
		"╚════════════════════════════════════════════════════╝" RESET
		"\n" BLUE "╔═══════════════════════════════════════════"
		"═════════╗" RESET "\n" BLUE "║" MARGENTA
		"                  Translation                       " BLUE "║"
		RESET "\n" BLUE "║" GREEN "    'w'    " YELLOW "   FRONT   "
		GREEN "     's'    " YELLOW "   BACK   " BLUE "        ║"
		"\n" BLUE "║" GREEN "    'd'  " YELLOW "     RIGHT    "
		GREEN "    'a'    " YELLOW "   LEFT  " BLUE "         ║" RESET BLUE "\n"
		BLUE "║" BLUE "                                                    ║"
		"\n"
		BLUE "║" MARGENTA "                    Rotation                     "
		BLUE "   ║" RESET "\n" BLUE "║" GREEN "  LEFT ARROW  " YELLOW
		" LEFT   " GREEN "     RIGHT ARROW  " YELLOW " RIGHT" BLUE "      ║""\n"
		BLUE "║" BLUE "                                                    ║"
		RESET "\n"
		BLUE "╚════════════════════════════════════════════════════╝" RESET
		"\n");
}

void	init_img_clean(t_main *cub)
{
	cub->picture.clean.mlx_img = mlx_new_image(cub->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	cub->picture.clean.addr = mlx_get_data_addr(cub->picture.clean.mlx_img,
			&cub->picture.clean.bpp, &cub->picture.clean.line_len,
			&cub->picture.clean.endian);
	cub->picture.clean.width = WINDOW_WIDTH;
	cub->picture.clean.height = WINDOW_HEIGHT;
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
	cub->img.mlx_img = mlx_new_image(cub->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.mlx_img, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	cub->img.width = WINDOW_WIDTH;
	cub->img.height = WINDOW_HEIGHT;
	init_img_clean(cub);
	cub->is_mini = 0;
	cub->show_texture = 1;
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	parsing_map(av, &main);
	config_player(&main.player);
	init_img(&main);
	image_inicialize(&main);
	ft_instruction();
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main);
	mlx_key_hook(main.win, deal_key, &main);
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_loop(main.mlx);
	return (0);
}
