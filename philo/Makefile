NAME		=	philo

CC			=	cc 
CFLAGS 		=	-Wall -Werror -Wextra -fPIE
INCLUDES	=	-lpthread
SRC			=	main.c actions.c converters.c string.c loggers.c\
				utils.c mutexes.c
OBJ			=	$(SRC:.c=.o)

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

all: $(NAME)

$(NAME): ${OBJ}
		@gcc ${OBJ} ${INCLUDES} -o ${NAME}

clean:
		@rm -rf ${OBJ}

fclean: clean
		@rm -rf ${NAME}

re: fclean ${NAME}
