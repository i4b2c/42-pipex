NAME = pipex

CC = cc
SRC = main.c
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

