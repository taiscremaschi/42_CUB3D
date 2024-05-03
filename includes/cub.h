/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paula <paula@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:59:07 by paula             #+#    #+#             */
/*   Updated: 2024/05/02 15:59:09 by paula            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../libft/gnl/get_next_line_bonus.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//////////// STRUCTS  //////////////

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;
	char *floor_color;
	char *ceiling_color;
	char **values;

}	t_textures;
typedef struct s_player
{
	int			x;
	int			y;
}				t_player;
//essa struct é da paula 
typedef struct s_picture
{
	void		*collectable;
	void		*wall;
	void		*player;
	void		*floor;
	void		*exit;
}				t_picture;

typedef struct s_main
{
	void		*win;
	char		**file_content;
	int			larg;
	int			altura;
	void		*mlx;
	int			moves_counter; // n preciso
	int			col; //n preciso
	t_player	player;
	t_picture	picture;
	t_textures	textures;
}				t_main;

///////////// VALIDATION //////////

void			map_paredes(t_main *main);
void			map_rectangle(t_main *main);
void			map_caracteres(t_main *main);
void			map_validate(t_main *main);
////////// MAPS ////////////

int				validate_characteres(char *line_map);
void			check_map(char **av, t_main *main);

///////////// CONTROLS ////////////
int				read_esc(int keycode, t_main *main);
void			verification_moves(t_main *m, int x, int y);
int				ft_strlen_sl(const char *s);

////////////// IMAGENS //////////////
void			image_inicialize(t_main *main);
int				render_image(t_main *main);

///////////  MAIN //////////
int				end(t_main *main);
void			free_map(char **m);

////////// ALGORITMO  /////////////
int				algoritmo(int x, int y, char **map_copy, int col);
char			**copy_map(t_main *main);
void			check_map_alg(t_main *main, char **copy_map_temp);


//////////////////// PARSING ///////////////////
void	parsing_map(char **av, t_main *main);
char	**save_file(char **map, int fd);


#endif
