NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux  -g3 #-fsanitize=address
SRCS = main.c\
		cast_rays.c\
		draw_loop.c\
		manage_map.c\
		manage_player.c\
		manage_mlx_loops_and_hooks.c\
		event_handlers.c\
		drawings.c\
		split.c	tools.c	tools2.c tools1.c\
		./get_next_line/get_next_line.c\
		./get_next_line/get_next_line_utils.c\
		./parsing/pars_and_initial.c\
		./parsing/color_element.c\
		./parsing/direction_element.c\
		./parsing/check_data.c\
		./parsing/check_data_tools.c\
		./parsing/read_file.c\
		./parsing/clean_work.c
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