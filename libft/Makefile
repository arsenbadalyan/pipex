# Variables
NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
EXECUTABLE = result
RM = rm -rf
AR = ar rc
RUN = ranlib
LIBS   = -I ../includes/

# Source Files
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c

# Object Files
OBJ = $(patsubst %.c, %.o, $(SRC))

# Colors
RESET  = \033[0m
GREEN  = \033[32m
BLUE   = \033[34m

# Rules
all: $(NAME)
	@echo ""

$(NAME): Makefile $(OBJ)
	@$(AR) $@ $(OBJ)
	@$(RUN) $@

%.o: %.c
	@echo "${BLUE}Compiling $^${RESET}"
	@$(CC) $(FLAGS) $(LIBS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re