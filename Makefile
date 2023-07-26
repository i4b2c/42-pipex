NAME = pipex

CC = cc
SRC = main.c \

CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

clean:
	@make clean -C libft/
	@rm -rf $(OBJ) arm*

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME)

re: fclean all
