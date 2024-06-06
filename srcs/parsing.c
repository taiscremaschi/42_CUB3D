/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:48:01 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/06/06 15:46:18 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	alloc_map(t_main *main)
{
	int	i;
	int	start;
	int	size;

	i = 0;
	size = 0;
	while (main->file_content[i] && main->file_content[i][0] == '\n')
		i++;
	start = i;
	while (main->file_content[i] != NULL)
	{
		i++;
		size++;
	}
	main->map = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (main->file_content[start] != NULL)
	{
		main->map[i] = ft_strdup(main->file_content[start]);
		i++;
		start++;
	}
	main->map[i] = NULL;
}

void	change_file_content(t_main *main)
{
	int	i;
	int	j;

	i = main->path.line_help;
	j = 0;
	while (i > 0)
	{
		free(main->file_content[j]);
		main->file_content[j] = ft_strdup("\n");
		i--;
		j++;
	}
	alloc_map(main);
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
