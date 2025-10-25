NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -g3 -fsanitize=address
SRCS = main.c\
		cast_rays.c\
		draw_loop.c\
		init_game.c\
		manage_map.c\
		manage_player.c\
		manage_mlx_loops_and_hooks.c\
		event_handlers.c\
		tools.c\
		drawings.c\
		 main.c	split.c	tools.c	tools2.c \
		./get_next_line/get_next_line.c	\
		./get_next_line/get_next_line_utils.c \
		./parsing/check_info.c	./parsing/pars_color.c	./parsing/pars_element.c \
		./parsing/pars_map2.c	./parsing/pars_map.c	./parsing/read_file.c tools1.c
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz
clean:
		rm -rf $(OBJS)
fclean: clean
		rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re
.SECONDARY: $(OBJS)