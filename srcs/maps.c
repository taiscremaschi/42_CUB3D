/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:05 by paula             #+#    #+#             */
/*   Updated: 2024/05/07 13:48:33 by tbolzan-         ###   ########.fr       */
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




// int	util_alg(int x, int y, char **map_copy)
// {
// 	if (map_copy[y][x] == '1' || map_copy[y][x] == 'z')
// 	{
// 		return (algoritmo(map_copy, x, y));
// 	}
// 	return (1);
// }


// int	algoritmo(char **map_copy, int x, int y)
// {

//     while(map_copy[y])
//     {
// 		x = 0;
//         while(map_copy[y][x] != '\0' && map_copy[y][x] != '\n')
//         {
//             while(map_copy[y][x] == ' ' || map_copy[y][x] == '\t')
//             {
// 				x++;
// 			}
//             if(map_copy[y][x] == '0' || map_copy[y][x] == 'S')
//             {
//                 if(map_copy[y][x] == '0')
//                 {
//                     if (util_alg(x, y - 1, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                     if (util_alg(x, y + 1, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                     if (util_alg(x + 1, y, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                     if (util_alg(x - 1, y, map_copy) == 0)
// 					{
// 	            		map_copy[y][x] = 'z';
//                         return (0);
// 					}
//                 }
//             }
//             x++;
// 			print_double_pointer(map_copy);
//         }
//         y++;
//     }
// 	return (1);
// }


