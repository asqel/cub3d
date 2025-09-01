MLX_PATH = minilibx-linux
MLX_NAME = libmlx.a

SRC = $(wildcard src/*.c src/*/*.c src/*/*/*.c src/*/*/*/*.c) main.c
OBJ = ${SRC:.c=.o}

NAME = cub3D

CC = cc
LD = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -Iminilibx-linux -g -O3
LDFLAGS = -lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ) $(MLX_PATH)/$(MLX_NAME)
	$(LD) -o $(NAME) $^ $(MLX_PATH)/$(MLX_NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(MLX_PATH)/$(MLX_NAME):
	make -C $(MLX_PATH)

clean:
	rm -rf $(OBJ)
	#make -C $(MLX_PATH) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette main.c src/ include/

#for f in assets/*.png ; do convert $f ${f/%png/xpm} ; done

.PHONY: re fclean clean all
