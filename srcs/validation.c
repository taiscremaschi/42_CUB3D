/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:11 by paula             #+#    #+#             */
/*   Updated: 2024/05/06 13:50:48 by tbolzan-         ###   ########.fr       */
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

void	map_paredes(t_main *main)
{
	int	i;
	int	altura;
	int	largura;

	i = -1;
	altura = main->altura - 1;
	largura = main->larg - 1;
	while (main->file_content[0][++i] != '\n')
	{
		if ((main->file_content[0][i] != '1'
				&& main->file_content[0][i] != '\n')
			|| (main->file_content[altura][i] != '1'
				&& main->file_content[altura][i] != '\n'))
		{
			free_map(main->file_content);
			exit(ft_putstr_fd("erro na parede de cima ou baixo\n", 1));
		}
	}
	i = -1;
	while (++i < altura)
	{
		if (main->file_content[i][0] != '1'
			&& main->file_content[i][largura] != '1')
		{
			free_map(main->file_content);
			exit(ft_putstr_fd("erro na parede dos lados\n", 1));
		}
	}
}

void	map_rectangle(t_main *main)
{
	int	alt;
	int	i;

	alt = 1;
	i = 1;
	main->larg = ft_strlen_sl(main->file_content[0]);
	while (main->file_content[i] != NULL)
	{
		if (main->larg == ft_strlen_sl(main->file_content[alt]))
		{
			alt++;
			i++;
		}
		else if (main->file_content[i][0] == '\n')
			i++;
	}
	main->altura = alt;
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
	while (main->file_content[i] != NULL)
	{
		if (validate_characteres(main->file_content[i]) == 0)
			i++;
		else
		{
			free_map(main->file_content);
			exit(ft_putstr_fd("Error: charactere invalid\n", 2));
		}
	}
}

void	validate_map(t_main *main)
{
	check_chars(main);
	check_and_save_player(main, "NSEW");
}