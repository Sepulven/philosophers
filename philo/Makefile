NAME		=	philo

CC			=	cc
CFLAGS 		=	-Wall -Werror -Wextra
INCLUDES	=	-lpthread
SRC			=	actions.c converters.c main.c string.c loggers.c\
				utils_1.c utils_2.c utils_3.c utils_4.c 
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
