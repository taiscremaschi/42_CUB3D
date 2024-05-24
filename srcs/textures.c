/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:09:59 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/14 08:52:30 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	save_textures(int *j, char *line, char **filename, int size)
{
	int	flag;

	flag = 0;
	*j += size;
	while (line[*j] == ' ' || line[*j] == '\t')
		(*j)++;
	if (line[*j] == '\n')
	{
		return (-1);
	}
	flag = *j;
	while (line[flag] != '\0' && line[flag] != ' ' && line[flag] != '\t'
		&& line[flag] != '\n')
		flag++;
	*filename = ft_substr(line, (*j), (flag - *j));
	*j = flag;
	return (1);
}

int	compare_args(char *line, int *j, t_main *main)
{
	int	count;

	count = 0;
	if (ft_strncmp(&line[*j], "NO ", 3) == 0)
		count += save_textures(j, line, &main->textures.north, 3);
	else if (ft_strncmp(&line[*j], "SO ", 3) == 0)
		count += save_textures(j, line, &main->textures.south, 3);
	else if (ft_strncmp(&line[*j], "WE ", 3) == 0)
		count += save_textures(j, line, &main->textures.west, 3);
	else if (ft_strncmp(&line[*j], "EA ", 3) == 0)
		count += save_textures(j, line, &main->textures.east, 3);
	else if (ft_strncmp(&line[*j], "F ", 2) == 0)
		count += save_textures(j, line, &main->textures.floor_color, 2);
	else if (ft_strncmp(&line[*j], "C ", 2) == 0)
		count += save_textures(j, line, &main->textures.ceiling_color, 2);
	else
		count = -1;
	return (count);
}

int	search_and_save_args(t_main *main, char *line)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	count = 0;
	while (main->file_content[++i] != NULL)
	{
		if (count == 6)
			break ;
		line = ft_strdup(main->file_content[i]);
		j = 0;
		while (line[j] != '\0' && line[j] != '\n')
		{
			while (line[j] != '\0' && (line[j] == ' ' || line[j] == '\t'))
				j++;
			count += compare_args(line, &j, main);
			if (line[j])
				j++;
		}
		if (line)
			free(line);
	}
	main->textures.line_help = i;
	return (count);
}

bool	acess_paths(t_main *main)
{
	if (access(main->textures.north, F_OK) == -1)
		return (false);
	if (access(main->textures.south, F_OK) == -1)
		return (false);
	if (access(main->textures.west, F_OK) == -1)
		return (false);
	if (access(main->textures.east, F_OK) == -1)
		return (false);
	return (true);
}
