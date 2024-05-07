/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:52 by paula             #+#    #+#             */
/*   Updated: 2024/05/07 19:26:57 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

bool check_x_left(char**map_copy, int x, int y)
{
	while(x >= 0)
	{
		if(map_copy[y][x] == '1')
			return true;
		if( map_copy[y][x] == '\n' || map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
			return false;
		x--;
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
	}
	return false;
}





