##
## EPITECH PROJECT, 2022
## 42sh
## File description:
## makefile
##

NAME	=	42sh

CC		=	gcc -g3
RM		=	rm -rf

SRC		=	$(shell find src -type f -name "*.c")

OBJ		=	$(SRC:.c=.o)

LIB		=	-Llib/my -lmy -lm -Iinclude -lncurses

WARN1	= 	-W -Wall -Wextra -pedantic -Wformat-nonliteral -Wformat-signedness \
			-Wundef -Wwrite-strings -Wcast-align \
			-Wstrict-overflow=5 -Wdeclaration-after-statement -Wvla \
			-Wpointer-arith -Winit-self -Wmissing-include-dirs \
			-Wdate-time -Wduplicated-branches -Wnull-dereference \
			-Wstack-usage=1024 -Winline -Wunsafe-loop-optimizations \
			-Wvla-larger-than=65536 -Wjump-misses-init \
			-Wlogical-not-parentheses -Wunused-result \
			-Wformat-security -Wformat-overflow=2 -Wdangling-else \
			-Wmissing-braces -Wtype-limits -Wshift-overflow=1 \
			-Wmissing-field-initializers -Wsync-nand \
			-Wpacked-not-aligned -Wmissing-parameter-type \
			-Warray-bounds=2

WARN2	= 	-Wconversion -Wunsuffixed-float-constants -Wmissing-prototypes \
			-Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code \
			-Wmissing-declarations -Wsequence-point -Waggregate-return \
			-Wstrict-prototypes -Wstringop-overflow=4 \
			-Wbool-operation -Wshift-overflow=2 \
			-Wsizeof-pointer-memaccess -Waddress \
			-Wdouble-promotion -Wformat-truncation=1 \
			-Wimplicit-fallthrough=5 -Wstrict-aliasing=2

WARN3	= 	-Wunused-macros -Warith-conversion \
			-Wunused-parameter -Wuninitialized -Wduplicated-branches \
			-Wparentheses -Wlogical-op -Wpacked \
			-Wmissing-noreturn -Wmissing-format-attribute -Wformat-signedness \
			-Wsizeof-pointer-memaccess -Wmemset-transposed-args -Wshadow=local \
			-Wshadow=compatible-local -Wclobbered -Wswitch-bool \
			-Wshift-negative-value -Wrestrict

WARN4	= 	-Wduplicated-cond -Wshadow -Wformat-overflow -Wformat-security \
			-Wnull-dereference -Wold-style-definition -Wredundant-decls \
			-Wnested-externs -Wbad-function-cast -Wcast-qual \
			-Wdisabled-optimization -Wshift-overflow=2 -Wdate-time \
			-Wvla-larger-than=65536 -Wformat -Wsuggest-final-methods \
			-Wsuggest-final-types -Wcast-function-type \
			-Wmaybe-uninitialized -Wstrict-overflow=4 -Wtrampolines \
			-Wvector-operation-performance -Walloc-zero \
			-Wsuggest-attribute=const -Wsuggest-attribute=noreturn \
			-Wsuggest-attribute=malloc -Wsuggest-attribute=pure \
			-Wsuggest-attribute=format

$(NAME):
		@make -s -C lib/my
		@$(CC) -o $(NAME) $(SRC) $(WARN1) $(WARN2) $(WARN3) $(WARN4) $(LIB)
		@rm lib/libmy.a
		@rm lib/my/libmy.a

all:	$(NAME)

clean:
		@$(RM) $(OBJ)
		@make -s -C lib/my clean
		@find . -name "*~" -delete -o -name "#*#" -delete
		@$(RM) vgcore.*
		@$(RM) a.out
		@find . -name *.gc* -delete

fclean:	clean
		@$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
