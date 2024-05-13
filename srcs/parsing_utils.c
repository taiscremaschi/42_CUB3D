/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:53:32 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/13 11:29:00 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	end_parsing(t_main *main, char *str)
{
	free_map(main->map);
	free(main->textures.ceiling_color);
	free(main->textures.south);
	free(main->textures.east);
	free(main->textures.west);
	free(main->textures.north);
	free(main->textures.floor_color);
	exit(ft_putstr_fd(str, 2));
}

void	inicialize_txt(t_main *main)
{
	main->textures.ceiling_color = NULL;
	main->textures.east = NULL;
	main->textures.floor_color = NULL;
	main->textures.north = NULL;
	main->textures.south = NULL;
	main->textures.west = NULL;
}

void	search_height(t_main *main)
{
	int	i;

	i = 0;
	while (main->map[i])
	{
		i++;
	}
	main->height = i;
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
		map_copy[i] = malloc(sizeof(char) * (ft_strlen(main->map[i])
					+ 1));
		if (!map_copy)
			return (NULL);
		while (main->map[i][j] != '\0')
		{
			map_copy[i][j] = main->map[i][j];
			j++;
		}
		map_copy[i][j] = '\0';
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
