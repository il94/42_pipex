NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCPATH = src/
SRC = main.c \
		initialize.c \
		get_paths.c \
		pipex.c \
		free_memory.c \
		here_doc.c

OBJ = $(SRC:.c=.o)

LIBFT = -L libft -lft


all : $(NAME)

$(NAME): $(OBJ)
	$(MAKE) --no-print-directory -C libft
	echo "\033[36mMaking Pipex\033[0m"
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -g
	echo "\033[32mDone\033[0m"

%.o : $(SRCPATH)%.c
	$(CC) $(CFLAGS) -c $^  -g

bonus : all

clean :
	$(MAKE) --no-print-directory fclean -C libft
	echo "\033[35mCleaning Pipex's objects...\033[0m"
	rm -f $(OBJ)
	echo "\033[32mDone\033[0m"

fclean :
	make clean
	echo "\033[35mCleaning Pipex...\033[0m"
	rm -f $(NAME)
	echo "\033[32mDone\033[0m"

re : fclean
	make all

.PHONY : all clean fclean re bonus
.SILENT :