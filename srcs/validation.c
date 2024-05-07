/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:11 by paula             #+#    #+#             */
/*   Updated: 2024/05/07 14:00:31 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_strlen_sl(const char *s)
{
	int	x;

	x = 0;
	while (s[x] != '\0' && s[x] != '\n')
		x++;
	return (x);
}


void	check_and_save_player(t_main *main, char *letters)
{
	int	i;
	int	j;
	int	flag_player;
	int	x;

	i = -1;
	flag_player = 0;
	while (main->file_content[++i] != NULL)
	{
		j = -1;
		while (main->file_content[i][++j] != '\0')
		{
			x = -1;
			while (++x < 4)
			{
				if (main->file_content[i][j] == letters[x] && flag_player == 0)
				{
					main->player.x = j;
					main->player.y = i;
					flag_player = 1;
					break ;
				}
				else if (main->file_content[i][j] == letters[x]
					&& flag_player == 1)
					exit(ft_putstr_fd("Error: more than one player\n", 2));
			}
		}
	}
}

int	validate_characteres(char *line_map)
{
	char	*valid_chars;
	int		i;
	int		j;

	i = 0;
	j = 0;
	valid_chars = "NSEW01\t\n ";
	while (line_map[j] != '\0')
	{
		if (line_map[j] == valid_chars[i])
		{
			j++;
			i = 0;
		}
		else if (i == 9)
		{
			
			printf("quebrou aqu\n");
			return (1);
		}
		else if (line_map[j] != valid_chars[i])
			i++;
		
	}
	return (0);
}

void	check_chars(t_main *main)
{
	int	i;

	i = 0;
	while (main->file_content[i] != NULL)
	{
		if (!validate_characteres(main->file_content[i]))
		{
			free_map(main->file_content);
			exit(ft_putstr_fd("Error: charactere invalid\n", 2));
		}
		i++;
	}
}

void	validate_map(t_main *main)
{
	check_chars(main);
	check_and_save_player(main, "NSEW");
	//check_map(main);
	search_height(main);
	//posso fazer uma coisa pra poupar linha se qualquer uma das validacoes
	//derem merda dou free aqui no mapa
}