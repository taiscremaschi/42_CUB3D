/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:52 by paula             #+#    #+#             */
/*   Updated: 2024/05/07 12:31:45 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void print_double_pointer(char **array) {
    for (int i = 0; array[i] != NULL; i++) {
        printf("%s", array[i]);
    }
}

// int	util_alg(int x, int y, char **map_copy)
// {
// 	if (map_copy[y][x] == '1' || map_copy[y][x] == 'z')
// 	{
// 		return (algoritmo(map_copy, x, y));
// 	}
// 	return (1);
// }


// int	algoritmo(char **map_copy, int x, int y)
// {

//     while(map_copy[y])
//     {
// 		x = 0;
//         while(map_copy[y][x] != '\0' && map_copy[y][x] != '\n')
//         {
//             while(map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
//             {
// 				x++;
// 			}
//             if(map_copy[y][x] == '0' || map_copy[y][x] == 'S')
//             {
//                 if(map_copy[y][x] == '0')
//                 {
//                     if (util_alg(x, y - 1, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                     if (util_alg(x, y + 1, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                     if (util_alg(x + 1, y, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                     if (util_alg(x - 1, y, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                 }
//             }
//             x++;
// 			print_double_pointer(map_copy);
//         }
//         y++;
//     }
// 	return (1);
// }



int check_zero(char**map_copy, int x, int y)
{
	int count = 0 ;
	while(map_copy[y])
	{
		x= 0 ;
		while(map_copy[y][x])
		{
			if(map_copy[y][x] == '0')
				count++;
			x++;
		}
		y++;
	}
	return (count);
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



void alg_tata(char **map_copy, int x, int y)
{
	int count  = check_zero(map_copy, x, y);
	while(map_copy[y])
	{
		x = 0;
		while(map_copy[y][x])
		{
			if(map_copy[y][x] == '1' || map_copy[y][x] == '\n' || map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
				x++;

			if(map_copy[y][x] == '0')	
				check_walls(map_copy, x, y)



		}
		y++;
	}
	
}




void	check_map_alg(t_main *main, char **copy_map_temp)
{
	if (copy_map_temp == NULL)
	{
		free_map(main->file_content);
		exit(ft_putstr_fd("Error in copy map\n", 2));
	}
	if (algoritmo(copy_map_temp, 0, 0) == 0)
	{
		//free_map(main->file_content);
		//free_map(copy_map_temp);
		exit(ft_putstr_fd("Error in the walls\n", 2));
	}
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