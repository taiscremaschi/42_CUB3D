/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:11 by paula             #+#    #+#             */
/*   Updated: 2024/05/03 20:16:30 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
		if ((main->file_content[0][i] != '1' && main->file_content[0][i] != '\n')
			|| (main->file_content[altura][i] != '1' && main->file_content[altura][i] != '\n'))
		{
			free_map(main->file_content);
			exit(ft_putstr_fd("erro na parede de cima ou baixo\n", 1));
		}
	}
	i = -1;
	while (++i < altura)
	{
		if (main->file_content[i][0] != '1' && main->file_content[i][largura] != '1')
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

// void search_map(t_main *main)
// {
	
	

	
// }

// char  **search_and_save_txt(int fd)
// {
// 	static int i;
// 	int j = 0;
// 	char *tmp;
	
// 	tmp = get_next_line(fd);
// 	while (tmp[j] != '\0' || tmp[j] != '\n')
// 	{
// 		if (tmp[j] == " " || tmp[j] == "\t")
// 			j++;
// 		if (tmp[j] == )
		

	
		
// 	}
	
	
	
	
	
	





// 	NO ./path_to_the_north_texture
// SO ./path_to_the_south_texture
// WE ./path_to_the_west_texture
// EA ./path_to_the_east_texture
// F 220,100,0
// C 225,30,0
	
// }

// void	check_letters(t_main *main, int i, int j, int *true_p)
// {
// 	if (main->file_content[i][j] == 'P')
// 	{
// 		(*true_p)++;
// 		main->player.x = j;
// 		main->player.y = i;
// 	}
// 	else if (main->file_content[i][j] == 'C')
// 		main->col++;
// }

void	map_caracteres(t_main *main)
{
	int	i;
	int	j;
	int	flag_player;
	int x; 
	char *letters;

	i = -1;
	flag_player = 0;
	main->col = 0;
	letters = "NSEW";
	
	while (main->file_content[++i] != NULL)
	{
		j = -1;
		while (main->file_content[i][++j] != '\0')
		{
			x = -1;
			while(++x < 4)
			{
				if (main->file_content[i][j] == letters[x] && flag_player == 0)
				{
					flag_player = 1;
					break ;
				}
				else if (main->file_content[i][j] == letters[x] && flag_player == 1)
					exit(ft_putstr_fd("Error in character\n", 2));
			}
		}
	}
			//check_letters(main, i, j, &true_p);	
}

void	map_validate(t_main *main)
{
	int	i;

	i = 0;
	while (main->file_content[i] != NULL)
	{
		if (validate_characteres(main->file_content[i]))
			i++;
		else
		{
			free_map(main->file_content);
			exit(ft_putstr_fd("Error in characteres\n", 1));
		}
	}
}
