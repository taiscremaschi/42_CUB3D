/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:05 by paula             #+#    #+#             */
/*   Updated: 2024/05/02 17:05:00 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_map(char **av, t_main *main)
{
	int	fd;

	if (ft_strchr(av[1], '.') == NULL || ft_strncmp(ft_strchr(av[1], '.'),
			".cub\0", 5) != 0)
		exit(write(1, "Error, wrong extension\n", 23));
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		exit(ft_putstr_fd("Error in opening FD\n", 1));
	main->map = save_map(NULL, fd);
	map_rectangle(main);
	map_validate(main);
	map_caracteres(main);
	map_paredes(main);
	//check_map_alg(main, copy_map(main));
}

int	validate_characteres(char *line_map)
{
	char	*valid_chars;
	int		i;
	int		count;

	i = 0;
	count = 0;
	valid_chars = "NSEW01\n ";
	while (line_map[count] != '\0')
	{
		if (line_map[count] == valid_chars[i])
		{
			count++;
			i = 0;
		}
		else if (i == 8)
			return (0);
		else if (line_map[count] != valid_chars[i])
			i++;
	}
	return (1);
}

char	**save_map(char **map, int fd)
{
	static int	i;
	char		*lines_map;

	lines_map = get_next_line(fd);
	if (lines_map)
	{
		i++;
		map = save_map(map, fd);
	}
	if (!map && i != 0)
		map = malloc(sizeof(char *) * (i + 1));
	if (!map)
		exit(ft_putstr_fd("Error, this map is false\n", 2));
	map[i--] = lines_map;
	return (map);
}
