NAME 		= fractol

CC 			= cc
RM			= rm -f

CFLAGS 		+= -Wall -Wextra -Werror -O3
CLINKS		= -ldl -lglfw -pthread -lm

MLX			= minilibx
LIBMLX 		= $(MLX)/libmlx42.a

FT			= libft
LIBFT		= $(FT)/libft.a

SRC 		= burning_ship.c\
			  fractol.c\
			  hook.c\
			  julia.c\
			  main.c\
			  mandelbrot.c\
			  mlx_utils.c\
			  multibrot.c
OBJ 		= $(SRC:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBMLX) $(CLINKS)

$(LIBMLX): $(MLX)
	cmake $(MLX) -B $(MLX)	
	$(MAKE) -C $(MLX)

$(LIBFT): $(FT)
	$(MAKE) -C $(FT)

$(MLX):
	git clone git@github.com:kodokaii/MLX42.git $(MLX)

$(FT):
	git clone git@github.com:kodokaii/libft_plus_plus.git $(FT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if [ -d "$(MLX)" ]; then $(MAKE) clean -C $(MLX); fi
	if [ -d "$(FT)" ]; then $(MAKE) clean -C $(FT); fi
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(LIBMLX)
	$(RM) $(LIBFT)
	$(RM) $(NAME)

clear: fclean
	$(RM) -r $(FT)
	$(RM) -r $(MLX) 

re: fclean all

.PHONY:		all bonus clear clean fclean re
