NO_COLOR= \x1b[0m
B_GRY	= \x1b[30;01m
B_RED	= \x1b[31;01m
B_GRN	= \x1b[32;01m
B_YEL	= \x1b[33;01m
B_BLU	= \x1b[34;01m
B_PURP	= \x1b[35;01m
B_TURQ	= \x1b[36;01m
B_WHT	= \x1b[37;01m
GRY		= \x1b[30m
RED		= \x1b[31m
GRN		= \x1b[32m
YEL		= \x1b[33m
BLU		= \x1b[34m
PURP	= \x1b[35m
TURQ	= \x1b[36m
WHT		= \x1b[37m
DIR		= ../42FileChecker/srcs/printf/speedtest_ft_printf.c
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
INC		= includes
NAME	= libftprintf.a

all: $(NAME)

$(NAME):
	make -C src/ re
	mv src/libftprintf.a ./

program:
	$(CC) -I $(INC) -c main.c -o main.o
	$(CC) $(CFLAGS) -I $(INC) main.o -L ./ -lftprintf -oprog
	./prog

speed:
	$(CC) -I $(INC) -c $(DIR) -o speedtest_ft_printf.o
	$(CC) $(CFLAGS) -I $(INC) speedtest_ft_printf.o -L ./ -lftprintf -ospeed
	time ./speed
	rm -f speed

re_pro: re program

clean:
	rm -f *.o
	make -C src/ clean

fclean: clean
	rm -f $(NAME)
	make -C src/ fclean

re: fclean all

.PHONY: clean fclean all re

