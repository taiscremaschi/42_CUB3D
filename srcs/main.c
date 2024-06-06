/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:59 by paula             #+#    #+#             */
/*   Updated: 2024/06/06 15:45:13 by paula            ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 2)
		exit(write(2, "Error\n", 6));
	parsing_map(av, &main);
	init_everything(&main);
	config_player(&main.player);
	ft_instruction();
	mlx_hook(main.win, 2, 1L << 0, read_esc, &main);
	mlx_key_hook(main.win, deal_key, &main);
	mlx_hook(main.win, 33, 1L << 2, end, &main);
	mlx_loop_hook(main.mlx, render_image, &main);
	mlx_loop(main.mlx);
	return (0);
}
