SRC = philo.c \
	ft_atoi.c \
	ft_isdigit.c \
	ft_split.c \
	ft_strjoin.c

OBJ = ${SRC:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

NAME = philo

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${SRC} -o ${NAME}

clean :
	${RM} ${OBJ}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re