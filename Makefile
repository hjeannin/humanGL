SRC_PATH	=	src/
OBJ_PATH	=	obj/
INC_PATH	=	inc/

SRCS		=	$(shell ls $(SRC_PATH) | grep .cpp$$)
OBJS		=	$(patsubst %.cpp, $(OBJ_PATH)%.o,$(SRCS))

PLATFORM	:=	$(shell uname)

HEADER		=	-I./$(INC_PATH) -I./compiled_GLFW/include/
FLAGS		=	-O3 -Wall -Wextra -Werror -std=gnu++11

CC			=	g++

ifeq "$(PLATFORM)" "Darwin" #MAC
GLFW		=	./compiled_GLFW/src/libglfw3_darwin.a
LIBS		=	$(GLFW) -lm -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
else ifeq "$(PLATFORM)" "Linux" #LINUX
GLFW		=	./compiled_GLFW/src/libglfw3_linux.a
LIBS		=	$(GLFW) -lGL -lXrandr -lXi -lXrender -ldrm -lXdamage -lXxf86vm -lXext -lX11 -lpthread -lXcursor -lm -lXinerama `libpng-config --libs` -lOpenCL -L/usr/local/cuda-6.5/lib64
endif

NAME		=	humanGL

all: $(NAME)
$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(HEADER) -o $(NAME) $(OBJS) $(LIBS)

$(patsubst %, $(OBJ_PATH)%,%.o): $(SRC_PATH)$(notdir %.cpp)
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $(FLAGS) $(HEADER) "$<" -o "$@"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

rl: re
	@./$(NAME)

ml: all
	@./$(NAME)

.PHONY: clean fclean re