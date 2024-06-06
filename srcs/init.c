/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:58:18 by paula             #+#    #+#             */
/*   Updated: 2024/06/06 10:18:22 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_everything(t_main *cub)
{
	cub->player.angle = 0;
	cub->player.vector_front.dx = 0;
	cub->player.vector_front.dy = 0;
	cub->player.vector_perpendicular.dx = 0;
	cub->player.vector_perpendicular.dy = 0;
}
