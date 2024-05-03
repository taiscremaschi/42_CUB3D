/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:07:05 by paula             #+#    #+#             */
/*   Updated: 2024/05/03 12:01:37 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"



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

