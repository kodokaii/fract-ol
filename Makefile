NAME 		= fractol
CC 			= cc
CFLAGS 		+= -Wall -Wextra -Werror -O3
CLINKS		= -ldl -lglfw -pthread -lm
LIBFT		= libft/libft.a
LIB 		= minilibx/libmlx.a
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

$(NAME): $(OBJ) $(LIBFT) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIB) $(CLINKS)

$(LIBFT): 
	$(MAKE) -C $$(dirname $(LIBFT))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $$(dirname $(LIBFT))
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY:		all debug clean fclean re
