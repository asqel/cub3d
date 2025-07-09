MLX_PATH = minilibx-linux
MLX_NAME = libmlx.a

SRC = $(wildcard src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c) main.c
OBJ = ${SRC:.c=.o}

NAME = cube3D

CC = cc
LD = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx-linux -g
LDFLAGS = -lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ) $(MLX_PATH)/$(MLX_NAME)
	$(LD) $(LDFLAGS) -o $(NAME) $^ $(MLX_PATH)/$(MLX_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(MLX_PATH)/$(MLX_NAME):
	$(MAKE) -C $(MLX_PATH)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all
