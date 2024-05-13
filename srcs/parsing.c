/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:48:01 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/13 17:45:03 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
	
void	change_file_content(t_main *main)
{
	int	i;
	int	j;
	int tmp;
	i = main->textures.line_help;
	j = 0;
	tmp = 0;
	int tmp2 = 0;
	while (i > 0)
	{
		free(main->file_content[j]);
		main->file_content[j] = ft_strdup("\n");
		i--;
		j++;
	}
	i = 0;
	j = 0;
	while(main->file_content[i][0] == '\n')
		i++;
	tmp2 = i;
	while(main->file_content[i] != NULL)
	{
		i++;
		tmp++;
	}
	main->map = malloc(sizeof(char *) * (tmp + 1));
	while(main->file_content[tmp2] != NULL)
	{
		main->map[j] = ft_strdup(main->file_content[tmp2]);
		j++;
		tmp2++;
	}
	main->map[j] = NULL;
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
	int	fd;

	fd = open(av[1], O_RDONLY);
	check_arg_and_fd(av, fd);
	main->file_content = save_file(NULL, fd);
	inicialize_txt(main);
	if (search_and_save_args(main, NULL) != 6)
		end_parsing(main, "Error in args of file\n");
	if (!acess_paths(main))
		end_parsing(main, "Error: path not found\n");
	if (!parsing_colors(main))
		end_parsing(main, "Error: colors error\n");
	change_file_content(main);
	search_height(main);
	validate_map(main);
}
