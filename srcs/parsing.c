/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:48:01 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/06 12:13:17 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	save_textures(int *j, char *line, char **filename, int size)
{
	int	flag;
	flag = 0;
	*j += size;
	while (line[*j] == ' ' || line[*j] == '\t')
		(*j)++;
    if (line[*j] == '\n')
    {
        return (-1);
    }
	flag = *j;
	while (line[flag] != '\0' && line[flag] != ' ' && line[flag] != '\t'
		&& line[flag] != '\n')
		flag++;
	*filename = ft_substr(line, (*j), (flag - *j));
	*j = flag;
	return (1);
}

int	compare_args(char *line, int *j, t_main *main)
{
	int	count;
    
	count = 0;
	if (ft_strncmp(&line[*j], "NO ", 3) == 0)
		count += save_textures(j, line, &main->textures.north, 3);
	else if (ft_strncmp(&line[*j], "SO ", 3) == 0)
		count += save_textures(j, line, &main->textures.south, 3);
	else if (ft_strncmp(&line[*j], "WE ", 3) == 0)
		count += save_textures(j, line, &main->textures.west, 3);
	else if (ft_strncmp(&line[*j], "EA ", 3) == 0)
		count += save_textures(j, line, &main->textures.east, 3);
	else if (ft_strncmp(&line[*j], "F ", 2) == 0)
		count += save_textures(j, line, &main->textures.floor_color, 2);
	else if (ft_strncmp(&line[*j], "C ", 2) == 0)
		count += save_textures(j, line, &main->textures.ceiling_color, 2);
	return (count);
}

int	search_and_save_args(t_main *main)
{
	int		i;
	int		j;
	char	*line;
	int		count;

	i = 0;
	count = 0;
	while (main->file_content[i] != NULL)
	{
		if(count == 6)
			break ;
		line = ft_strdup(main->file_content[i]);
		j = 0;
		while (line[j] != '\0' && line[j] != '\n')
		{
			while ((line[j] != '\0' && line[j] == ' ') || line[j] == '\t')
				j++;
			count += compare_args(line, &j, main);
			j++;
		}
		if (line)
			free(line);
		i++;
	}
	main->textures.line_help = i;
	return (count);
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

void inicialize_txt(t_main *main)
{
    main->textures.ceiling_color = NULL;
    main->textures.east = NULL;
    main->textures.floor_color = NULL;
    main->textures.north  = NULL;
    main->textures.south  = NULL;
    main->textures.west  = NULL;
    
}


void change_file_content(t_main *main)
{
	int i = main->textures.line_help;
	int j  = 0;

	while(i > 0)
	{
		main->file_content[j] = NULL;;
		main->file_content[j] = "\n";
		i--;
		j++;
	}
}

void print_double_pointer(char **array) 
{
    for (int i = 0; array[i] != NULL; i++) 
	{
        printf("%s", array[i]);
    }
}

void	parsing_map(char **av, t_main *main)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	check_arg_and_fd(av, fd);
	main->file_content = save_file(NULL, fd); // file content salva todo meu arquivo.
    inicialize_txt(main); //aqui pode ser uma funcao para inicializar all que chama o inicialize txt 
	if (search_and_save_args(main) != 6)
		exit(ft_putstr_fd("Error in args of file\n", 2));
	change_file_content(main);
	//print_double_pointer(main->file_content);
	// separar o mapa dos paths
	// verificar se o mapa esta correto com os caracteres depois as paredes
	// com uma especie de flood fill
	map_rectangle(main); // esse n preciso
	map_validate(main);
	map_caracteres(main);
	map_paredes(main);
	// check_map_alg(main, copy_map(main));
}
