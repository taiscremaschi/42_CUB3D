/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:48:01 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/03 11:26:05 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// char  **search_and_save_txt(int fd)
// {
    
// }


void check_arg_and_fd(char **av, int fd)
{
	if (ft_strchr(av[1], '.') == NULL || ft_strncmp(ft_strchr(av[1], '.'),
			".cub\0", 5) != 0)
		exit(write(1, "Error, wrong extension\n", 23));
	if (fd <= 0)
		exit(ft_putstr_fd("Error in opening FD\n", 1));
    
}

void	parsing_map(char **av, t_main *main)
{
	int	fd;
	fd = open(av[1], O_RDONLY);
    check_arg_and_fd(av, fd);
	main->map = save_map(NULL, fd);
	map_rectangle(main);
	map_validate(main);
	map_caracteres(main);
	map_paredes(main);
	//check_map_alg(main, copy_map(main));
}