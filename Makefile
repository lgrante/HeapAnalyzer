##
## EPITECH PROJECT, 2018
## makefile
## File description:
## main makefile
##

SRC		=	src/malloc.c \
			src/free.c \
			src/calloc.c \
			src/realloc.c \
			src/reallocarray.c \
			src/debug.c

OBJ		=	$(SRC:.c=.o)

CFLAGS		=	-Wall -fpic -I./include

NAME		=	libmy_malloc.so

CC		=	@gcc

RM		=	rm -f

block-nb	=	-1

all: 		$(NAME)

$(NAME):	$(OBJ)
		@printf "\e[1m\e[38;2;21;124;214mCompiling $(NAME)...\033[0m  "
		@$(CC) -o $(NAME) -shared $(OBJ) 
		@printf "Done.\n"

clean:
		@printf "\e[1m\e[38;2;21;124;214mCleaning all object files...\033[0m  "
		@$(RM) build/$(OBJ)
		@printf "Done.\n"

fclean:		clean
		@printf "\e[1m\e[38;2;21;124;214mCleaning $(NAME)...\033[0m  "
		@$(RM) $(NAME)
		@printf "Done.\n"

re:		fclean all

test:
		@printf "Running test...\n"

debug:		CFLAGS	+=	-ggdb
debug:		CFLAGS 	+=	-DDEBUG_MODE -DBLOCK_NB=$(block-nb)
debug:		re
		@printf "\e[1m\e[38;2;21;124;214mSetting debug mode...\033[0m  "
		@printf "Done.\n"

doc:
		@nohup firefox ./doc.html &
		@$(RM) nohup.out

.PHONY: all clean fclean re debug doc
