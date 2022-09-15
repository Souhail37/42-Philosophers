SRC = philo.c \
	utils/ft_atoi.c \
	utils/ft_isdigit.c \
	utils/ft_split.c \
	utils/ft_strjoin.c\
	philo_tools.c \
	init_philo.c \
	checker_philo.c \
	ft_time.c

OBJ = ${SRC:.c=.o}

CC = gcc

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