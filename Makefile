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

FEATURE_FLAGS =

# Define installation directory
INSTALL_DIR = /usr/local/bin
INSTALL_FILES = golf_gti_MKII

all:    $(NAME)

$(NAME):    $(OBJ)
			gcc $(FEATURE_FLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

clean :
	        rm -f $(OBJ)

fclean :	 clean
			rm -f $(NAME)

re : 		fclean all

debug:    CFLAGS += -g
debug:    re

install: FEATURE_FLAGS += -DINTALL_MODE
install: re
		cp $(NAME) $(INSTALL_DIR)
		cp $(INSTALL_FILES) $(INSTALL_DIR)
		chmod 755 $(INSTALL_DIR)/$(NAME)

uninstall:
		rm -f $(INSTALL_DIR)/$(NAME)
		rm -f $(INSTALL_DIR)/$(INSTALL_FILES)


