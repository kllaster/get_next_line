NAME			= get_next_line.a
CC				= gcc
RM				= rm -f
LIB				= ar rc
MKDIR			= mkdir -p
DEBUG			= 1
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
endif
COMMON_FLAGS	= -Wall -Wextra -Werror -MMD -c -D BUFFER_SIZE=500
CFLAGS			= $(COMMON_FLAGS) -march=native -O2 -msse4a -flto -pipe

BIN_DIR			= bin/
BUILD_DIR		= build/
HEADERS			= include/

SRCS			= srcs/get_next_line.c\
			  	  srcs/get_next_line_utils.c\

OBJS			= $(notdir $(SRCS))
OBJS			:= $(OBJS:%.c=$(BUILD_DIR)%.o)
DEPS			= $(OBJS:.o=.d)
NAME 			:= $(addprefix $(BIN_DIR), $(NAME))

all:			$(NAME)

$(NAME):		$(OBJS)
				$(MKDIR) $(dir $@)
				$(LIB) $(NAME) $(OBJS)
				ranlib $(NAME)

$(OBJS):		$(SRCS)
				$(MKDIR) $(dir $@)
				$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
				$(RM) $(OBJS)
				$(RM) $(DEPS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

-include		$(DEPS)
.PHONY:			all, clean, fclean, re
