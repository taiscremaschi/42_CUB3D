/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:48:01 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/08 11:29:12 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void change_file_content(t_main *main)
{
	int i = main->textures.line_help;
	int j  = 0;

	while(i > 0)
	{
		free(main->file_content[j]);
		main->file_content[j] = ft_strdup("\n");
		i--;
		j++;
	}
}

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

void	check_arg_and_fd(char **av, int fd)
{
	if (ft_strchr(av[1], '.') == NULL || ft_strncmp(ft_strchr(av[1], '.'),
			".cub\0", 5) != 0)
		exit(write(2, "Error, wrong extension\n", 23));
	if (fd <= 0)
		exit(ft_putstr_fd("Error in opening FD\n", 2));
}

void	parsing_map(char **av, t_main *main)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	check_arg_and_fd(av, fd); //checa a extensaoo cub e chega se o fd deu certo.
	main->file_content = save_file(NULL, fd); // file content salva todo meu arquivo.
    inicialize_txt(main);
	search_height(main); //aqui pode ser uma funcao para inicializar all que chama o inicialize txt 
	if (search_and_save_args(main) != 6)
	{
		end_parsing(main);
		exit(ft_putstr_fd("Error in args of file\n", 2));
	}
	if(!acess_paths(main))
	{
		end_parsing(main);
		exit(ft_putstr_fd("Error: path not found\n", 2));
	}
	change_file_content(main); //agr meu arquivo esta sem os args hehehehhe ohhhhhhhhhh yessss.
	validate_map(main);
}
