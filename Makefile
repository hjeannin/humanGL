
SRC_PATH	=	src/
OBJ_PATH	=	obj/
INC_PATH	=	inc/

SRCS		=	$(shell ls $(SRC_PATH) | grep .cpp$$)
OBJS		=	$(patsubst %.cpp, $(OBJ_PATH)%.o,$(SRCS))

HEADER		=	-I./$(INC_PATH) -I$(HOME)/.brew/include
LIBS		=	-L$(HOME)/.brew/lib
FLAGS		=	-Wall -Wextra -Werror
NAME		=	humanGL

CC			=	g++

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $^ $(HEADER) $(LIBS) -lsfml-graphics -lsfml-window -lsfml-system

$(patsubst %, $(OBJ_PATH)%,%.o): $(SRC_PATH)$(notdir %.cpp)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $(FLAGS) $(HEADER) "$<" -o "$@"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
