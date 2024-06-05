/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:09:59 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/29 09:18:05 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	save_path(int *j, char *line, char **filename, int size)
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
	if (ft_strncmp(&line[*j], "NO ", 3) == 0 && !main->path.north)
		count += save_path(j, line, &main->path.north, 3);
	else if (ft_strncmp(&line[*j], "SO ", 3) == 0 && !main->path.south)
		count += save_path(j, line, &main->path.south, 3);
	else if (ft_strncmp(&line[*j], "WE ", 3) == 0 && !main->path.west)
		count += save_path(j, line, &main->path.west, 3);
	else if (ft_strncmp(&line[*j], "EA ", 3) == 0 && !main->path.east)
		count += save_path(j, line, &main->path.east, 3);
	else if (ft_strncmp(&line[*j], "F ", 2) == 0 && !main->path.floor_color)
		count += save_path(j, line, &main->path.floor_color, 2);
	else if (ft_strncmp(&line[*j], "C ", 2) == 0
		&& !main->path.ceiling_color)
		count += save_path(j, line, &main->path.ceiling_color, 2);
	else
		count = -1;
	return (count);
}

int	search_and_save_args(t_main *main, char *line)
{
	int	i;
	int	j;
	int	count;

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
	main->path.line_help = i;
	return (count);
}

bool	acess_paths(t_main *main)
{
	if (access(main->path.north, F_OK) == -1)
		return (false);
	if (access(main->path.south, F_OK) == -1)
		return (false);
	if (access(main->path.west, F_OK) == -1)
		return (false);
	if (access(main->path.east, F_OK) == -1)
		return (false);
	return (true);
}
