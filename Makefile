.SILENT:

NAME = cub3D

SRC = check_walls.c image.c validation.c parsing.c textures.c algorithm.c parsing_utils.c end_game_utils.c \
		parsing_colors.c raycasting.c player.c moves.c utils_image.c render.c draw.c init.c
MAIN = main.c
SRCS = $(SRC) $(MAIN)

OBJS = $(addprefix objs/, $(SRCS:.c=.o))

FLAGS = -Wall -Wextra -g -Werror -fsanitize=address

COLOUR_GREEN=\033[32m
COLOUR_RED=\033[31m
COLOUR_END=\033[0m
COLOUR_MAG=\001\e[0;35m\002

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx_linux
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
ifeq ($(shell uname), Linux)
	MLX_DIR = ./mlx_linux
	MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	MLX_DIR = ./mlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

objs/%.o: */%.c
	@mkdir -p objs
	@cc ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: ${NAME}

install:
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette -U
	sudo apt update
	sudo apt install valgrind -y

check:
	norminette ./libft
	norminette ./srcs
	norminette ./includes/cub.h

${NAME}: ${OBJS}
	@echo "$(COLOUR_GREEN)----Compiling lib----"
	@make --no-print-directory re -C ./libft
	@make --no-print-directory -C ./mlx_linux
	@cc $(FLAGS) $(OBJS) -Llibft -lft -o $(NAME) $(MLX_FLAGS)
		@echo "  $(COLOUR_MAG)                                                                        ";
	@echo "💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟";
	@echo "                                __  _   _  ___  ____ ___   _                           ";
	@echo "                              / __|| | | || _ )|__ /|   \ | |                          ";
	@echo "                             | (__ | |_| || _ \ |_ \| |) ||_|                          ";
	@echo "                              \___| \___/ |___/|___/|___/ (_)                          ";
	@echo "                                                                  By tbolzan-          ";
	@echo "                                                                     pde-souz          ";
	@echo "💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟";
	@echo "                                                                                         ";
	@echo "$(COLOUR_GREEN)cub3D Compiled! ᕦ$(COLOUR_RED)♥$(COLOUR_GREEN)_$(COLOUR_RED)♥$(COLOUR_GREEN)ᕤ\n$(COLOUR_END)"
	@echo "$(COLOUR_MAG)\nTo start the program type ./cub3D <map.cub> \nENJOY!\n$(COLOUR_END)"

test:
	cd cub3d-tester ; bash test-map-errors.sh;
	# cd cub3d-tester ; bash test-map-weird.sh;

clean:
	@make --no-print-directory clean -C ./libft
	@rm -f ${OBJS}
	@echo "$(COLOUR_RED)Deleting all objs! ⌐(ಠ۾ಠ)¬\n$(COLOUR_END)"

fclean: clean
	@make --no-print-directory fclean -C ./libft
	@rm -f ${NAME}
	@clear
	
re:			fclean all

valgrind: clean fclean all
	valgrind --leak-check=full ./cub3D maps/our_map.cub
	valgrind --leak-check=full ./cub3D maps/map_err_map.cub

map: clean fclean all
	./cub3D maps/map_area.cub
	./cub3D maps/map_color1.cub
	./cub3D maps/map_err_arg.cub
	./cub3D maps/map_err_color.cub
	./cub3D maps/map_err_map.cub
	./cub3D maps/map_err_mpre_player.cub
	./cub3D maps/map_err_path.cub
	./cub3D maps/map_err_player.cub
	./cub3D maps/map_err_wall.cub
	./cub3D maps/map_err_wall2.cub

.PHONY: all clean fclean re 
