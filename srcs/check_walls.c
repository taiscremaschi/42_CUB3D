/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:52 by paula             #+#    #+#             */
/*   Updated: 2024/05/06 15:35:17 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"


int	util_alg(int x, int y, char **map_copy)
{
	if (map_copy[y][x] != '1' && map_copy[y][x] != 'z')
	{
		return (algoritmo(x, y, map_copy));
	}
	return (1);
}


int	algoritmo(int j, int i, char **map_copy, int height)
{
    int	i;
    int j = 0;
	int	largura;

	i = 0;

    while(map_copy[i])
    {
        j = 0;
        while(map_copy[i][j] != '\0' && map_copy[i][j] != '\n')
        {
            while(map_copy[i][j] == ' ' || map_copy[i][j] == '\t')
                j++;
            if(map_copy[i][j] == '0')
            {
                
            }       
            
            
        }
        i++;
    }
    if (map_copy[j][i] == '0')
    {
        //procuro se acho 1.
    }
    if(map_copy[j][i] == '1')
    
	map_copy[i][j] = 'z';

	if (util_alg(j, i - 1, map_copy) == 0)
		return (0);
	if (util_alg(j, i + 1, map_copy) == 0)
		return (0);
	if (util_alg(j + 1, i, map_copy) == 0)
		return (0);
	if (util_alg(j - 1, i, map_copy) == 0)
		return (0);
	return (1);
}


void	check_map_alg(t_main *main, char **copy_map_temp)
{
	if (copy_map_temp == NULL)
	{
		free_map(main->file_content);
		exit(ft_putstr_fd("Error in copy map", 2));
	}
	if (algoritmo(main->player.x, main->player.y, copy_map_temp, main->height) == 1)
	{
		free_map(main->file_content);
		free_map(copy_map_temp);
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