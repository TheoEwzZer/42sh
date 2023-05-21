##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

SRC	    =   $(shell find -type f -name "*.c")

OBJ     =	$(SRC:.c=.o)

NAME_L	=	libmy.a

NAME_H	=	my.h

all:	$(NAME_L)

$(NAME_L):	$(OBJ)
	    ar rc $(NAME_L) $(OBJ)
	    cp $(NAME_L) ../$(NAME_L)
	    cp $(NAME_H) ../../include/$(NAME_H)
	    make clean

clean:
	    rm -f $(OBJ)
