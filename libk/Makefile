CC =		gcc

CFLAG =		-O0 -ffreestanding -m32 -nostdlib -fno-stack-protector -Wall -Wextra -Werror

NAME =		libk.a

SRC =		memmove.c \
            memcpy.c \
            memcmp.c \
            strlen.c \
            memset.c

OBJ =		$(SRC:.c=.o)

all: 		$(NAME)

$(NAME): 	$(OBJ)
			@echo "Creating libk with an index..."
			@ar rcs $@ $^
			@echo "libk.a is ready !"

%.o: %.c
			@echo Compiling $<
			@$(CC) $(CFLAG) -I. -o $@ -c $<

clean:
			@rm -rf $(OBJ)

fclean:		clean
			@rm -rf $(NAME)

re: 		fclean all
