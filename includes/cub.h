/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:57:32 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/08/09 12:32:52 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/gnl/get_next_line_bonus.h"
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define UP 119
# define DOWN 115
# define RIGHT 65363
# define LEFT 65361
# define W_UP 119
# define AA_LEFT 97
# define D_RIGHT 100
# define S_DOWN 115
# define TEXTURE 116

//	Screen Resolution
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 800
# define PI 3.1415926535f
# define ANGLE_0 0
# define ANGLE_180 PI

//	Minimap Resolution
# define MINI_WIDTH 20
# define WINDOW_HEIGHT 800

// HIT
# define EXTRA_STEP 2

// COLOR
# define CLR_N 0xFF5500
# define CLR_S 0x20B2AA
# define CLR_E 0xFF63A7
# define CLR_W 0xFFD7A0

// TEXTURES
# define TEX_HEIGTH 64
# define TEX_WIDTH 64

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MARGENTA "\x1b[35m"
# define RESET "\033[0m"

//////////// STRUCTS  //////////////
// refatorar as structs

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_draw_wall
{
	int			draw_start;
	int			draw_end;
	int			color;
	double		wall_x;
	t_img		text;
}				t_draw_wall;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

typedef struct s_coordint
{
	int			x;
	int			y;
}				t_coordint;

typedef struct s_vector
{
	double		dx;
	double		dy;
}				t_vector;

typedef struct s_vectorint
{
	int			dx;
	int			dy;
}				t_vectorint;

typedef struct s_raycast
{
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_vectorint	step;
	t_vectorint	map;
	double		perp_wall_dist;
	int			hit;
	int			side;
	int			line_height;
	char		hit_direction;
	int			tex_x;
	int			tex_y;
}				t_raycast;

typedef struct s_path
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
}				t_path;

typedef struct s_ctrl
{
	int			press_w;
	int			press_s;
	int			press_a;
	int			press_d;
	int			press_q;
	int			press_e;
	int			press_r;
	int			press_l;
	int			press_speed;
	int			counter;
}				t_ctrl;

typedef struct s_player
{
	double		x;
	double		y;
	t_vector	vector_front;
	t_vector	vector_perpendicular;
	char		position;
	double		angle;
}				t_player;

typedef struct s_picture
{
	t_img		p_north;
	t_img		p_south;
	t_img		p_west;
	t_img		p_east;
	t_img		wall2d;
	t_img		floor2d;
	t_img		clean;
}				t_picture;

typedef struct s_main
{
	void		*win;
	char		**file_content;
	char		**map;
	int			height;
	void		*mlx;
	int			is_mini;
	int			show_texture;
	t_rgb		rgb;
	t_img		img;
	t_player	player;
	t_picture	picture;
	t_path		path;
	t_ctrl		moves;
}				t_main;

int				init_everything(t_main *cub);
void			my_mlx_destroy_image(void *mlx_ptr, void *img_ptr);

/////////////////////////// ALGORITHM //////////////////
void			check_map_with_alg(t_main *main, char **copy_map_temp);
void			change_player(char **map_copy, int x, int y);
bool			alg_walls(char **map_copy, int x, int y, int height);
void			rotate2(double angle, t_vector *vector);
void			rotate_player(t_player *player, double dangle);
/////////////////////////// CHECK WALLS  //////////////////

bool			check_x_left(char **map_copy, int x, int y);
bool			check_x_right(char **map_copy, int x, int y);
bool			check_y_up(char **map_copy, int x, int y);
bool			check_y_down(char **map_copy, int x, int y, int height);

int				player_hit(t_main *cub, t_vector dir, double pos_x,
					double pos_y);

////////////////////////////// IMAGES //////////////
int				image_inicialize(t_main *main);
int				render_image(t_main *main);

////////////////////////////// END GAME UTILS ///////////////
int				end(t_main *main);
void			free_map(char **m);
int				read_esc(int keycode, t_main *main);
int				end_2(t_main *main, t_img *img);

/////////////////////////// PARSING UTILS //////////////////
void			inicialize_txt(t_main *main);
void			search_height(t_main *main);
char			**copy_map(t_main *main);
void			end_parsing(t_main *main, char *str);
bool			check_args_colors(char **color_content);

//////////////////// PARSING ///////////////////
void			change_map(t_main *main);
char			**save_file(char **map, int fd);
void			check_arg_and_fd(char **av, int fd);
void			parsing_map(char **av, t_main *main);

/////////////////////////// TEXTURES  //////////////////
int				save_path(int *j, char *line, char **filename, int size);
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

//////////////////////////////// RAYCASTING //////////////////
void			start_ray(t_raycast *ray, double cameraX, t_main *cub,
					t_vector pos);
void			ray_steps(t_raycast *ray, t_vector pos);
void			performing_dda(t_raycast *ray, t_main *cub);
void			draw_wall(t_raycast *ray, t_main *cub, int x_screen,
					t_vector pos);

//////////////////////////////// PLAYER //////////////////
void			config_player(t_player *player);
void			rotate_player(t_player *player, double dangle);
void			rotate2(double angle, t_vector *vector);
int				player_hit(t_main *cub, t_vector dir, double pos_x,
					double pos_y);
int				deal_key(int key, t_main *cub);
void			moves_up_down(int key, t_main *cub, t_vector dir);
void			moves_rl(int key, t_main *cub, t_vector dir);
void			ui_options(t_main *cub, int key);

//////////////////////////////// DRAW //////////////////
void			put_2d_image(t_main *main, int x, int y, char c);
void			draw_player(t_main *cub);
// new
void			bresenham_line(t_main *cub, t_vector start, t_vector end,
					int color);
//
void			print_wall(int x_screen, t_main *cub, t_draw_wall wall);
void			ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void			ft_mlx_put_image_frame(t_img *frame, int x, int y,
					t_img *image);
void			draw_wall(t_raycast *ray, t_main *cub, int x_screen,
					t_vector pos);
void			config_draw_color(t_main *cub, t_raycast *ray,
					t_draw_wall *wall, char c);
int				get_pixel(t_img *image, int x, int y);
void			put_2d_image_floor(t_main *main, int x, int y);
#endif
