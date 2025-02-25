NAME = cub3D

LIBRARY_DIR = ./libft
MLX = ./mlx_linux/libmlx.a
LIBFT = $(LIBRARY_DIR)/libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -g

RM = rm -f

SRCS = src/main.c src/utils.c src/controls.c src/keyboard.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(PRINTF) -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) 

$(LIBFT):
	@$(MAKE) -C $(LIBRARY_DIR) all

$(MLX): 
	@$(MAKE) -C ./mlx_linux

clean:
	@$(MAKE) -C $(LIBRARY_DIR) clean
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) -C $(LIBRARY_DIR) fclean
	@$(MAKE) -C ./mlx_linux clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re