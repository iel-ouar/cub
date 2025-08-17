NAME = cub
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
LINK_FLAGS = -lmlx -lXext -lX11

CFILES = main.c	split.c	tools.c	tools2.c \
	./get_next_line/get_next_line.c	\
	./get_next_line/get_next_line_utils.c \
	./parsing/check_info.c	./parsing/pars_color.c	./parsing/pars_element.c \
	./parsing/pars_map2.c	./parsing/pars_map.c	./parsing/read_file.c




OBJS = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LINK_FLAGS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.SECONDARY : $(OBJS)
.PHONY : clean