/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:06:41 by paula             #+#    #+#             */
/*   Updated: 2024/08/09 12:14:04 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	load_texture(t_img *img, t_main *cub, char *texture_path)
{
	img->mlx_img = mlx_xpm_file_to_image(cub->mlx, texture_path, &img->width,
		&img->height);
	if (img->mlx_img == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len,
		&img->endian);
	return (0);
}

int	image_inicialize(t_main *main)
{
	if (load_texture(&main->picture.p_north, main, main->path.north) == 1)
		return (1);
	if (load_texture(&main->picture.p_west, main, main->path.west) == 1)
		return (1);
	if (load_texture(&main->picture.p_east, main, main->path.east) == 1)
		return (1);
	if (load_texture(&main->picture.p_south, main, main->path.south) == 1)
		return (1);
	if (load_texture(&main->picture.floor2d, main,
			"./texture/map2d/floor.xpm") == 1)
		return (1);
	if (load_texture(&main->picture.wall2d, main,
			"./texture/map2d/wall.xpm") == 1)
		return (1);
	return (0);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (y >= 0 && x >= 0 && y < img->height && x < img->width)
	{
		dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dest = color;
	}
}

void	ft_mlx_put_image_frame(t_img *frame, int x, int y, t_img *image)
{
	char	*dest;
	char	*src;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++j < image->height)
	{
		while (++i < image->width)
		{
			if ((y + j) > frame->height || (x + i) > frame->width)
				continue ;
			dest = frame->addr + ((y + j) * frame->line_len + (x + i)
				* (frame->bpp / 8));
			src = image->addr + (j * image->line_len + i * (image->bpp / 8));
			*(unsigned int *)dest = *(unsigned int *)src;
		}
		i = -1;
	}
}

void	put_2d_image(t_main *main, int x, int y, char c)
{
	if (c == 'w')
	{
		if (main->map[y][x] == '1')
			ft_mlx_put_image_frame(&main->img, (x * MINI_WIDTH), (y
					* MINI_WIDTH), &main->picture.wall2d);
	}
	if (c == 'f')
	{
		if ((main->map[y][x] != '\n' && main->map[y][x] != ' ')
			|| main->map[y][x] == '0')
			ft_mlx_put_image_frame(&main->img, (x * MINI_WIDTH), (y
					* MINI_WIDTH), &main->picture.floor2d);
	}
}
