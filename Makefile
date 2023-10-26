##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## make files
##

SRC     =	main.c		\

OBJ     =	$(SRC:.c=.o)

NAME    =   gti


CFLAGS  = -Wall -Wextra

LDFLAGS = -lncurses

# Define installation directory
INSTALL_DIR = /usr/local/bin
INSTALL_FILES = golf_gti_MKII

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

debug:	CFLAGS += -g
debug:	re

install:
	sed -i '1s/^/#define INSTALL_MODE 1\n/' main.c
	make re
	sed -i '1d' main.c
	cp $(NAME) $(INSTALL_DIR)
	cp $(INSTALL_FILES) $(INSTALL_DIR)
	chmod 755 $(INSTALL_DIR)/$(NAME)
	make fclean

uninstall:
	rm -f $(INSTALL_DIR)/$(NAME)
	rm -f $(INSTALL_DIR)/$(INSTALL_FILES)


