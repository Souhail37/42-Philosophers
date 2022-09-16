SRC_BONUS = philo_bonus.c \
		utils_bonus/ft_atoi.c \
		utils_bonus/ft_isdigit.c \
		utils_bonus/ft_split.c \
		utils_bonus/ft_strjoin.c\
		philo_bonus_tools.c \
		init_philo_bonus.c \
		checker_philo_bonus.c \
		ft_time_bonus.c

OBJ = $(SRC_BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

NAME = philo_bonus

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(SRC_BONUS) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re