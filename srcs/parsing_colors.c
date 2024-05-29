/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:02:26 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/29 10:17:22 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	save_color(t_main *main, int tmp, int i, char type)
{
	if (type == 'c')
	{
		if (i == 0)
			main->path.ceiling_rgb.r = tmp;
		if (i == 1)
			main->path.ceiling_rgb.g = tmp;
		if (i == 2)
			main->path.ceiling_rgb.b = tmp;
	}
	if (type == 'f')
	{
		if (i == 0)
			main->path.floor_rgb.r = tmp;
		if (i == 1)
			main->path.floor_rgb.g = tmp;
		if (i == 2)
			main->path.floor_rgb.b = tmp;
	}
}

bool	check_args_colors(char **color_content)
{
	int		i;

	i = 0;
	while (color_content[i])
		i++;
	if (i != 3)
	{
		free_map(color_content);
		return (false);
	}
	return (true);
}

bool	check_color_digit(char **color_content)
{
	int	i;
	int	j;

	i = 0;
	while (color_content[i])
	{
		j = 0;
		while (color_content[i][j])
		{
			if (ft_isdigit(color_content[i][j]) == 0)
				j++;
			else
			{
				free_map(color_content);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	search_colors(t_main *main, char *color, char type)
{
	char	**color_content;
	int		i;
	int		tmp;

	color_content = ft_split(color, ',');
	i = 0;
	tmp = 0;
	if (!check_args_colors(color_content))
		return (false);
	if (!check_color_digit(color_content))
		return (false);
	while (color_content[i])
	{
		tmp = ft_atoi(color_content[i]);
		if (tmp < 0 || tmp > 255)
		{
			free_map(color_content);
			return (false);
		}
		save_color(main, tmp, i, type);
		i++;
	}
	free_map(color_content);
	return (true);
}

bool	parsing_colors(t_main *main)
{
	if (!search_colors(main, main->path.ceiling_color, 'c'))
		return (false);
	if (!search_colors(main, main->path.floor_color, 'f'))
		return (false);
	return (true);
}
