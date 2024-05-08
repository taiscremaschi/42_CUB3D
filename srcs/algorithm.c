/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:52:19 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/08 11:31:14 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


bool alg_walls(char **map_copy, int x, int y, int height)
{
	while(map_copy[y] != NULL)
	{
		x = 0;
		while(map_copy[y][x] != '\0' || map_copy[y][x] != '\n')
		{
			if(map_copy[y][x] == '\0' || map_copy[y][x] == '\n')
				break ;
			else if(map_copy[y][x] == '1' || map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
				x++;
			else if(map_copy[y][x] == '0')
			{
				if (!check_y_down(map_copy, x, y, height) || !check_y_up(map_copy, x, y))
						return false;
				if(!check_x_left(map_copy, x, y) || !check_x_right(map_copy, x, y))
					return false;
				x++;
			}
			else 
				x++;
		}
		y++;
	}
	return true;	
}

void change_player(char **map_copy, int x, int y)
{
	char p;
	
	while(map_copy[y])
	{
		x = 0;
		while(map_copy[y][x])
		{
			p = map_copy[y][x];
			if(p == 'N' || p == 'S' || p == 'E' || p == 'W')
			{
				map_copy[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	return ;
}

void	check_map_with_alg(t_main *main, char **copy_map_temp)
{
	if (copy_map_temp == NULL)
	{
		end_parsing(main);
		exit(ft_putstr_fd("Error in copy map\n", 2));
	}
	change_player(copy_map_temp, main->player.x, main->player.y);
	if(alg_walls(copy_map_temp, 0, 0, main->height) == false)
	{
		end_parsing(main);
		free_map(copy_map_temp);
		exit(ft_putstr_fd("Error in the walls\n", 2));
	}
	printf("oh yes mapa certo espero \n");
	free_map(copy_map_temp);
}