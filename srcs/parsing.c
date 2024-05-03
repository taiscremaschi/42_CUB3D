/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:48:01 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/03 12:25:29 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// char  **search_and_save_txt(int fd)
// {
// }

char	**save_file(char **map, int fd)
{
	static int	i;
	char		*lines_file;

	lines_file = get_next_line(fd);
	if (lines_file)
	{
		i++;
		map = save_file(map, fd);
	}
	if (!map && i != 0)
		map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		exit(ft_putstr_fd("Error, file is wrong\n", 2));
	map[i--] = lines_file;
	return (map);
}

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
	main->file_content = save_file(NULL, fd);
    //separar o mapa dos paths 
    //verificar os paths se estao corretos
    //verificar se o mapa esta correto com os caracteres depois as paredes 
    // com uma especie de flood fill 
	map_rectangle(main); //esse n preciso
	map_validate(main);
	map_caracteres(main);
	map_paredes(main);
	//check_map_alg(main, copy_map(main));
}