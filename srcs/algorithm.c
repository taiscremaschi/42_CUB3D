/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:52:19 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/06/06 15:45:59 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

bool	alg_walls(char **map, int x, int y, int height)
{
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0' || map[y][x] != '\n')
		{
			if (map[y][x] == '\0' || map[y][x] == '\n')
				break ;
			else if (map[y][x] == '1' || map[y][x] == ' ' || map[y][x] == '\t')
				x++;
			else if (map[y][x] == '0')
			{
				if (!check_y_down(map, x, y, height) || !check_y_up(map, x, y))
					return (false);
				if (!check_x_left(map, x, y) || !check_x_right(map, x, y))
					return (false);
				x++;
			}
			else
				x++;
		}
		y++;
	}
	return (true);
}

void	change_player(char **map_copy, int x, int y)
{
	char	p;

	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			p = map_copy[y][x];
			if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
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
		end_parsing(main, "Error in copy map\n");
	change_player(copy_map_temp, main->player.x, main->player.y);
	if (alg_walls(copy_map_temp, 0, 0, main->height) == false)
	{
		free_map(copy_map_temp);
		end_parsing(main, "Error in the walls\n");
	}
	free_map(main->file_content);
	free_map(copy_map_temp);
}
