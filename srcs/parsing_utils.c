/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:53:32 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/07 15:02:11 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void search_height(t_main *main)
{
    int i = 0;
    while(main->file_content[i])
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