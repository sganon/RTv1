# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sganon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:32:31 by sganon            #+#    #+#              #
#    Updated: 2016/06/01 16:34:26 by sganon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	rtv1

SRC =	main.c \
		init.c \
		key_events.c \
		parsing.c \
		camera_parsing.c \
		object_parsing.c \
		object_parsing2.c \
		light_parsing.c \
		ray_cast.c \
		light_cast.c \
		plane.c \
		math_vector.c \
		rotate.c \
		rotate_object.c \
		rotate_cam.c \
		shadow.c \
		abc.c \
		draw_in_img.c \
		specular.c \

SRC_LIST =	$(addprefix srcs/, $(SRC))

O_FILES = $(SRC:.c=.o)

O_LIST = $(addprefix objs/, $(O_FILES))

CC = gcc

CC_FLAGS = -Wall -Werror -Wextra -Ofast

LIBFT_FLAG = -L./libft -lft

MLX_FLAG = -L./mlx -lmlx -framework AppKit -framework OpenGL 

INC_FLAG = -I./includes

all : $(NAME)

$(NAME): 
		@make -C libft/ fclean
		@make -C mlx/ clean
		@make -C libft/
		@make -C mlx/ libmlx.a
		@echo "Libft and mlx compiled."
		@$(CC) $(CC_FLAGS) -c $(SRC_LIST) $(INC_FLAG)
		@echo "Objects compiled."
		@rm -rf objs/
		@mkdir objs/
		@mv $(O_FILES) ./objs/
		@$(CC) $(CC_FLAGS) -o $(NAME) $(O_LIST) $(LIBFT_FLAG) $(MLX_FLAG) -lm $(INC_FLAG)
		@echo "RTv1 compiled."

clean:
		@rm -rf objs/
		@make -C libft/ fclean
		@make -C mlx/ clean
		@echo "Objects and libraries cleaned."

fclean : clean
		@rm -f $(NAME)
		@echo "RTv1 cleaned."

re : fclean all

.PHONY : all clean fclean re
