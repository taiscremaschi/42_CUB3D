/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:52 by paula             #+#    #+#             */
/*   Updated: 2024/05/07 13:48:20 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"



void check_player(char **map_copy, int x, int y)
{
	while(map_copy[y])
	{
		x= 0 ;
		while(map_copy[y][x])
		{
			if(map_copy[y][x] == 'N' || map_copy[y][x] == 'S')
			{
				map_copy[y][x] = '0';
				return ;
			}
			if(map_copy[y][x] == 'E' || map_copy[y][x] == 'W')
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

bool check_x_left(char**map_copy, int x, int y)
{
	while(x >= 0)
	{
		x--;
		if(map_copy[y][x] == '1')
			return true;
		if( map_copy[y][x] == '\n' || map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
			return false;
		if( map_copy[y][x] == '0')
			continue ;
	}
	return false;
	
}

bool check_x_right(char**map_copy, int x, int y)
{
	while(map_copy[y][++x] != '\0')
	{
		if(map_copy[y][x] == '1')
			return true;
		if( map_copy[y][x] == '\n' || map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
			return false;
		if( map_copy[y][x] == '0')
			continue ;
	}
	return false;
}


bool check_y_up(char**map_copy, int x, int y)
{
	while(y > 0)
	{
		y--;
		if(map_copy[y][x] == '1')
			return true;
		if( map_copy[y][x] == '\n' || map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
			return false;
		if( map_copy[y][x] == '0')
			continue ;
	}
	return false;
}

bool check_y_down(char**map_copy, int x, int y, int height)
{
	while( y < (height -1))
	{
		y++;
		if(map_copy[y][x] == '1')
			return true;
		if( map_copy[y][x] == '\n' || map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
			return false;
		if( map_copy[y][x] == '0')
			continue ;
	}
	return false;
}


bool alg_tata(char **map_copy, int x, int y, int height)
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

void	check_map_alg(t_main *main, char **copy_map_temp)
{
	if (copy_map_temp == NULL)
	{
		free_map(main->file_content);
		exit(ft_putstr_fd("Error in copy map\n", 2));
	}
	check_player(copy_map_temp, main->player.x, main->player.y);
	if(alg_tata(copy_map_temp, 0, 0, main->height) == false)
	{
		//free_map(main->file_content);
		//free_map(copy_map_temp);
		exit(ft_putstr_fd("Error in the walls\n", 2));
	}
	// if (algoritmo(copy_map_temp, 0, 0) == 0)
	// {
	// 	//free_map(main->file_content);
	// 	//free_map(copy_map_temp);
	// 	exit(ft_putstr_fd("Error in the walls\n", 2));
	// }
	printf("oh yes mapa certo espero \n");
	free_map(copy_map_temp);
}



char	**copy_map(t_main *main)
{
	char	**map_copy;
	int		i;
	int		j;

	map_copy = malloc(sizeof(char *) * (main->height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < main->height)
	{
		j = 0;
		map_copy[i] = malloc(sizeof(char) * (ft_strlen(main->file_content[i]) + 1));
		if (!map_copy)
			return (NULL);
		while (main->file_content[i][j] != '\0')
		{
			map_copy[i][j] = main->file_content[i][j];
			j++;
		}
		map_copy[i][j] = '\0';
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}