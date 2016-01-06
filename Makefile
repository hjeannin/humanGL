
SRC_PATH	=	src/
OBJ_PATH	=	obj/
INC_PATH	=	inc/

SRCS		=	$(shell ls $(SRC_PATH) | grep .cpp$$)
OBJS		=	$(patsubst %.cpp, $(OBJ_PATH)%.o,$(SRCS))

HEADER		=	-I./$(INC_PATH) -I/nfs/zfs-student-2/users/hjeannin/.brew/Cellar/sfml/2.3_1/include
FLAGS		=	-Wall -Wextra -Werror
LIBS		=	-L/nfs/zfs-student-2/users/hjeannin/.brew/Cellar/sfml/2.3_1/lib -lsfml-graphics -lsfml-window -lsfml-system
NAME		=	humanGL

CC			=	clang++

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(HEADER) $(LIBS) $(OBJS) -o $(NAME)

$(patsubst %, $(OBJ_PATH)%,%.o): $(SRC_PATH)$(notdir %.cpp)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $(FLAGS) $(HEADER) "$<" -o "$@"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re
