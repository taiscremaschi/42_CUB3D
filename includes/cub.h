/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:57:32 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/13 14:05:27 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define UP 119
# define DOWN 115
# define RIGHT 100
# define LEFT 97

//////////// STRUCTS  //////////////

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor_color;
	char		*ceiling_color;
	t_rgb		floor_rgb;
	t_rgb		ceiling_rgb;
	int			line_help;
}				t_textures;

typedef struct s_player
{
	int			x;
	int			y;
	char		position;
}				t_player;

typedef struct s_picture
{
	void		*p_north;
	void		*p_south;
	void		*p_west;
	void		*p_east;
}				t_picture;

typedef struct s_main
{
	void		*win;
	char		**file_content;
	int			height;
	void		*mlx;
	t_player	player;
	t_picture	picture;
	t_textures	textures;
}				t_main;

/////////////////////////// ALGORITHM //////////////////
void			check_map_with_alg(t_main *main, char **copy_map_temp);
void			change_player(char **map_copy, int x, int y);
bool			alg_walls(char **map_copy, int x, int y, int height);

/////////////////////////// CHECK WALLS  //////////////////

bool			check_x_left(char **map_copy, int x, int y);
bool			check_x_right(char **map_copy, int x, int y);
bool			check_y_up(char **map_copy, int x, int y);
bool			check_y_down(char **map_copy, int x, int y, int height);

////////////////////////////// IMAGES //////////////
void			image_inicialize(t_main *main);
int				render_image(t_main *main);

////////////////////////////// END GAME UTILS ///////////////
int				end(t_main *main);
void			free_map(char **m);
int				read_esc(int keycode, t_main *main);

/////////////////////////// PARSING UTILS //////////////////
void			inicialize_txt(t_main *main);
void			search_height(t_main *main);
char			**copy_map(t_main *main);
void			end_parsing(t_main *main, char *str);

//////////////////// PARSING ///////////////////
void			change_file_content(t_main *main);
char			**save_file(char **map, int fd);
void			check_arg_and_fd(char **av, int fd);
void			parsing_map(char **av, t_main *main);

/////////////////////////// TEXTURES  //////////////////
int				save_textures(int *j, char *line, char **filename, int size);
int				compare_args(char *line, int *j, t_main *main);
int				search_and_save_args(t_main *main, char *line);
bool			acess_paths(t_main *main);

///////////// VALIDATION //////////
int				check_and_save_player(t_main *main, char *letters, int player,
					int i);
int				validate_characteres(char *line_map);
void			check_chars(t_main *main);
void			validate_map(t_main *main);

//////////////////////////////// PARSING COLORS //////////////////
void			save_color(t_main *main, int tmp, int i, char type);
bool			search_colors(t_main *main, char *color, char type);
bool			parsing_colors(t_main *main);
bool			check_color_digit(char **color_content);
bool			check_args_colors(char **color_content);

#endif
