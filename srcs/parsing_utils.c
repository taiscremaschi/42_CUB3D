/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:53:32 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/29 10:16:48 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	end_parsing(t_main *main, char *str)
{
	if (main->map)
		free_map(main->map);
	free_map(main->file_content);
	free(main->path.ceiling_color);
	free(main->path.south);
	free(main->path.east);
	free(main->path.west);
	free(main->path.north);
	free(main->path.floor_color);
	exit(ft_putstr_fd(str, 2));
}

void	inicialize_txt(t_main *main)
{
	main->path.ceiling_color = NULL;
	main->path.east = NULL;
	main->path.floor_color = NULL;
	main->path.north = NULL;
	main->path.south = NULL;
	main->path.west = NULL;
	main->map = NULL;
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
		map_copy[i] = malloc(sizeof(char) * (ft_strlen(main->map[i]) + 1));
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
