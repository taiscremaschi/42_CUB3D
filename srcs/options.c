/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:12:11 by paula             #+#    #+#             */
/*   Updated: 2024/06/07 18:12:49 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ui_options(t_main *cub, int key)
{
	if (!cub->show_texture && key == 't')
		cub->show_texture = 1;
	else if (cub->show_texture && key == 'c')
		cub->show_texture = 0;
	else if (key == '2')
		cub->is_mini = 1;
	else if (key == '3')
		cub->is_mini = 0;
}
