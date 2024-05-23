CLR_RMV := \033[0m
RED := \033[1;31m
GREEN := \033[1;32m
YELLOW := \033[1;33m
BLUE := \033[1;34m
CYAN := \033[1;36m

CC = cc
CFLAGS = -Wall -Wextra -Werror
PFLAG = -pthread
DFLAG = -fsanitize=thread -g
NAME = philo
RM = rm -rf

SRC = main.c \
      errors.c \
      checkers.c \
      initializing.c \
      cleanup.c \
      debugging_statements.c \
      routines.c \
      times.c \
      ft_functions.c \
      print_output.c \
      single_philo.c \
      monitoring.c \
      forks.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) $(PFLAG) -o $@
	@echo "$(GREEN)Philos ready to munch$(CLR_RMV)"

fsanitize: $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) ($DFLAG) $(PFLAG) -o $@
	@echo "$(GREEN)Philos ready to munch with fsanitize$(CLR_RMV)"

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Removing object files$(CLR_RMV)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removing executable$(CLR_RMV)"

re: fclean all

.PHONY: all clean fclean re
