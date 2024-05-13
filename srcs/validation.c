/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:11 by paula             #+#    #+#             */
/*   Updated: 2024/05/13 14:29:58 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_and_save_player(t_main *main, char *letters, int player, int i)
{
	int	j;
	int	x;

	while (main->map[++i] != NULL)
	{
		j = -1;
		while (main->map[i][++j] != '\0')
		{
			x = -1;
			while (++x < 4)
			{
				if (main->map[i][j] == letters[x])
				{
					if (player)
						end_parsing(main, "Error: more than one player\n");
					main->player.x = j;
					main->player.y = i;
					main->player.position = letters[x];
					player = 1;
				}
			}
		}
	}
	return (player);
}

int	validate_characteres(char *line_map)
{
	char	*valid_chars;
	int		i;
	int		j;

	i = 0;
	j = 0;
	valid_chars = "NSEW01\t\n ";
	while (line_map[j] != '\0' && line_map[j] != '\n')
	{
		if (line_map[j] == valid_chars[i])
		{
			j++;
			i = 0;
		}
		else if (i == 9)
			return (1);
		else if (line_map[j] != valid_chars[i])
			i++;
	}
	return (0);
}

void	check_chars(t_main *main)
{
	int	i;

	i = 0;
	while (main->map[i] != NULL)
	{
		if (validate_characteres(main->map[i]) == 1)
			end_parsing(main, "Error: charactere invalid\n");
		i++;
	}
}

void	validate_map(t_main *main)
{
	check_chars(main);
	if (check_and_save_player(main, "NSEW", 0, -1) == 0)
		end_parsing(main, "Error: no player in game\n");
	check_map_with_alg(main, copy_map(main));
}
