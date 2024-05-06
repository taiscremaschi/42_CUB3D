

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
	char *floor_color; //falta o parsing para cores
	char *ceiling_color;
	int	 line_help;
}	t_textures;

typedef struct s_player
{
	int			x;
	int			y;
}				t_player;

typedef struct s_picture
{
	void		*p_north;
	void		*p_south;
	void 		*p_west;
	void 		*p_east;
}				t_picture;

typedef struct s_main
{
	void		*win;
	char		**file_content;
	int			larg; //tbm acho que n usarei
	int			height; //acho que nao preciso
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
void			check_chars(t_main *main);
void			validate_map(t_main *main);


////////// MAPS ////////////

int				validate_characteres(char *line_map);

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
int				algoritmo(char **map_copy, int col);
char			**copy_map(t_main *main);
void			check_map_alg(t_main *main, char **copy_map_temp);


//////////////////// PARSING ///////////////////
void	parsing_map(char **av, t_main *main);
char	**save_file(char **map, int fd);


/////////////////////// textures ////////////////

void inicialize_txt(t_main *main);
int	search_and_save_args(t_main *main);

////////////////utils que nao sei onde por ainda ///
void search_height(t_main *main);

#endif
