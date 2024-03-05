NAME = imgts

SRC = main.c src/data.c src/bitmap_operations.c

CC = cc
FLAGS = -g -fsanitize=address -static-libasan #-Wall -Wextra -Werror -g
DFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -static-libsan
PRINT_FLAG = -D PRINT_NUMBER_OF_EATS=1

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(FLAGS) $(PRINT_FLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test:
	@gcc test.c -o test
	@./test

rtest:
	@./test

.PHONY: all clean fclean re
