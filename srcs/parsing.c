/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:48:01 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/03 14:21:25 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int search_and_save_args(t_main *main)
{
    int i = 0;
    int j;
    char *line;
    int flag = 0;
    int check_paths = 0; 
    while(main->file_content[i]!= NULL)
    {
        line = ft_substr(main->file_content[i], 0, ft_strlen(main->file_content[i]));
        
        j = 0;
        while (line[j] != '\0' && line[j] != '\n')
        {
            while ((line[j] != '\0' && line[j] == ' ' )|| line[j] == '\t')
                j++;
            if(ft_strncmp(&line[j], "NO ", 3) == 0)
            {
                j += 4;
                flag = j;
                while(line[flag] != ' ' || line[flag] != '\t' || line[flag] != '\n' || line[flag] != '\0')
                    flag++;
                main->textures.north = ft_substr(line, (j), (flag - j));
                j = flag;
                check_paths++;
            }
            if(ft_strncmp(&line[j], "SO ", 3) == 0)
            {
                j += 4;
                flag = j;
                while(line[flag] != ' ' || line[flag] != '\t' || line[flag] != '\n' || line[flag] != '\0')
                    flag++;
                main->textures.south = ft_substr(line, (j), (flag - j));
                j = flag;
                check_paths++;

            }
            if(ft_strncmp(&line[j], "WE ", 3) == 0)
            {
                j += 4;
                flag = j;
                while(line[flag] != ' ' || line[flag] != '\t' || line[flag] != '\n' || line[flag] != '\0')
                    flag++;
                main->textures.west= ft_substr(line, (j), (flag - j));
                j = flag;
                check_paths++;

            }
            if(ft_strncmp(&line[j], "EA ", 3) == 0)
            {
                j += 4;
                flag = j;
                while(line[flag] != ' ' || line[flag] != '\t' || line[flag] != '\n' || line[flag] != '\0')
                    flag++;
                main->textures.east = ft_substr(line, (j), (flag - j));
                j = flag; 
                check_paths++;

            }
            if(ft_strncmp(&line[j], "F ", 2) == 0)
            {
                j += 3;
                flag = j;
                while(line[flag] != ' ' || line[flag] != '\t' || line[flag] != '\n' || line[flag] != '\0')
                    flag++;
                main->textures.floor_color = ft_substr(line, (j), (flag - j));
                j = flag;   
                check_paths++;

            }
            if(ft_strncmp(&line[j], "C ", 2) == 0)
            {
                j += 3;
                flag = j;
                while(line[flag] != ' ' || line[flag] != '\t' || line[flag] != '\n' || line[flag] != '\0')
                    flag++;
                main->textures.ceiling_color = ft_substr(line, (j), (flag - j));
                j = flag;
                check_paths++;
            }
            j++;
        }
        if(line)
            free (line);
        i++;
    }
    if(check_paths != 6)
		exit(ft_putstr_fd("Error in args of file\n", 2));
    return 0;
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

void check_arg_and_fd(char **av, int fd)
{
	if (ft_strchr(av[1], '.') == NULL || ft_strncmp(ft_strchr(av[1], '.'),
			".cub\0", 5) != 0)
		exit(write(2, "Error, wrong extension\n", 23));
	if (fd <= 0)
		exit(ft_putstr_fd("Error in opening FD\n", 2));
    
}

void	parsing_map(char **av, t_main *main)
{
	int	fd;
	fd = open(av[1], O_RDONLY);
    check_arg_and_fd(av, fd);
	main->file_content = save_file(NULL, fd);
    //verificar os paths se estao corretos
    search_and_save_args(main);
    //separar o mapa dos paths 
    //verificar se o mapa esta correto com os caracteres depois as paredes 
    // com uma especie de flood fill 
	map_rectangle(main); //esse n preciso
	map_validate(main);
	map_caracteres(main);
	map_paredes(main);
	//check_map_alg(main, copy_map(main));
}