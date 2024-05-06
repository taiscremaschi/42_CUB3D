/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:05 by paula             #+#    #+#             */
/*   Updated: 2024/05/06 14:42:04 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"



//FUNCOES LIXO MAS QU EPOSSO ME INSPIRAR 


// void	map_paredes(t_main *main)
// {
// 	int	i;
// 	int	height;
// 	int	largura;

// 	i = -1;
// 	height = main->height - 1;
// 	largura = main->larg - 1;
// 	while (main->file_content[0][++i] != '\n')
// 	{
// 		if ((main->file_content[0][i] != '1'
// 				&& main->file_content[0][i] != '\n')
// 			|| (main->file_content[height][i] != '1'
// 				&& main->file_content[height][i] != '\n'))
// 		{
// 			free_map(main->file_content);
// 			exit(ft_putstr_fd("erro na parede de cima ou baixo\n", 1));
// 		}
// 	}
// 	i = -1;
// 	while (++i < height)
// 	{
// 		if (main->file_content[i][0] != '1'
// 			&& main->file_content[i][largura] != '1')
// 		{
// 			free_map(main->file_content);
// 			exit(ft_putstr_fd("erro na parede dos lados\n", 1));
// 		}
// 	}
// }


void search_height(t_main *main)
{
    int i = 0;
    int j = 0 ;
    while(main->file_content[i])
    {
        i++;
    }
    main->height = i;
}
