NAME = ft_chip8
SRC =   srcs/main.c \
        srcs/gfx.c \
        srcs/utils.c \
        srcs/chip8.c \
        srcs/key.c \
        srcs/execute_code.c

OBJ = $(SRC:.c=.o)
CXX = cc
CXXFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lSDL3
MAKEFLAGS += --silent -j

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)
	echo "build done."

clean:
	@rm -f $(OBJ)
	echo "object(s) cleaned."

fclean: clean
	@rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
	$(MAKE) clean

.PHONY: all clean fclean re