NAME = MiniRT

SRCS = fixed.c vector_arithmetic.c mlx_test.c pixels.c
OBJS = $(SRCS:.c=.o)

CC = gcc
#CFLAGS = -Wall -Wextra -Werror
#LDFLAGS = -Lmlx_linux -lmlx_linux -L/mlx-linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

CFLAGS = -Wall -Wextra -Werror -I/mlx-linux -Imlx-linux
LDFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
#-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	rm -f $(OBJS)
	echo "Objects removed."

fclean: clean
	rm -rf $(NAME)
	echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re
