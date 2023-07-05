##
## EPITECH PROJECT, 2023
## eitech
## File description:
## momo
##

CC 		= 	gcc

MAIN	=	SRC/main/main.c

FILES	=	$(wildcard ./SRC/*.c)

SRC 	=	$(MAIN)		\
			$(FILES)

RM 		= 	rm -f

NAME 	= 	myftp

CFLAGS 	= 	-Wall -Werror -I include/

OBJ		=	$(SRC:.c=.o)



all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)
	find . -name '*~' -delete -o -name '#*#' -delete -o -name '*.gcno' \
		-delete -o -name -'*.gcdo' -delete -o -name '*.gcda' -delete

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re
