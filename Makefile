NAME = fdf
CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRCS = main.c \
       ft_split.c \
       utils.c \
	   parse_map.c \
	   draw_map.c \
	   free_func.c

GNL_DIR = get_next_line/
GNL_SRCS = $(GNL_DIR)get_next_line.c \
           $(GNL_DIR)get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)

INC_DIR = -I. -I$(GNL_DIR) -Iminilibx-linux

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS) $(GNL_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re