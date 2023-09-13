NAME	=		test

S		=		src/

O		=		obj/

H		=		 

FILES	=		main.c

SRCS	=	$(addprefix $S, $(FILES))

LIBFT	=

MLX		=		

OBJS	=		$(SRCS:$S%.c=$O%.o)

CC		=		gcc

CFLAGS	=		#-Wall -Werror -Wextra

UNAME	=		$(shell uname -s)
ifeq ($(UNAME),Linux)
	H += -I lib/mlx_linux
	MLX += -L lib/mlx_linux -l mlx -lXext -lX11 -lm -lz
endif
ifeq ($(UNAME),Darwin)
	H += -I lib/mlx_mac
	MLX += -L lib/mlx_mac -l mlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$O%.o: $S%.c
	@[ -d $O ] || mkdir $O
	@$(CC) $(CFLAGS) $H -c $< -o $@

$(NAME): $(OBJS)
	@bash mlx_install.sh
	@$(CC) $(CFLAGS) $H $(SRCS) $(LIBFT) $(MLX) -o $(NAME)

clean:
	@rm -rf $O

fclean: clean
	@bash mlx_install.sh
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
