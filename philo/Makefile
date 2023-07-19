NAME		=	philo

CC			=	cc
CFLAGS 		=	-Wall -Werror -Wextra
INCLUDES	=	-lpthread
SRC			=	main.c
OBJ			=	$(SRC:.c=.o)

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $<  -o $@

all: $(NAME)

$(NAME): ${OBJ}
		@gcc ${OBJ} ${INCLUDES} -o ${NAME}

clean:
		@rm -rf ${OBJ}

fclean: clean
		@rm -rf ${NAME}

re: fclean ${NAME}
