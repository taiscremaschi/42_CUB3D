/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braseham.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:45:05 by paula             #+#    #+#             */
/*   Updated: 2024/06/07 13:03:00 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	max(float x, float y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

static float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

void	bresenham_line(t_main *cub, t_vector start, t_vector end,
		int color)
{
	t_coord del;
	int		max_num;

    del.x = end.dx - start.dx;
	del.y = end.dy - start.dy;
	max_num = max(mod(del.x), mod(del.y));
	del.x /= max_num;
	del.y /= max_num;
	while ((int)(start.dx - end.dx) || (int)(start.dy - end.dy))
	{
		ft_mlx_pixel_put(&cub->img, start.dx, start.dy, color);
		start.dx += del.x;
		start.dy += del.y;
	}
}
