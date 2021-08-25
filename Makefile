NAME			= get_next_line.a
CC				= gcc
RM				= rm -f
LIB				= ar rc
MKDIR			= mkdir -p
DEBUG			= 0
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS	= -fsanitize=address -g
else
	DEBUG_FLAGS = -O2 -flto -D_FORTIFY_SOURCE=2 -fpie
endif
PROTECT_FLAGS	= -fno-exceptions -fstack-protector-all
COMMON_FLAGS	= -std=c99 -Wall -Wextra -Werror -Wfloat-equal -MMD -pipe
MAKEFLAGS		= -j --output-sync=recurse --no-print-directory
CFLAGS			= $(COMMON_FLAGS) $(DEBUG_FLAGS) $(PROTECT_FLAGS) -D BUFFER_SIZE=32

BIN_DIR			= bin/
SRC_DIR			= srcs
BUILD_DIR		= build
INC_DIR			= include

SRCS			= $(shell find $(SRC_DIR) -name "*.c")

OBJS			= $(notdir $(SRCS))
OBJS			:= $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.c=%.o))
NAME			:= $(addprefix $(BIN_DIR), $(NAME))
DEPS			= $(OBJS:.o=.d)
VPATH			= $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

all:			$(NAME)

$(NAME):		$(OBJS)
				$(MKDIR) $(dir $@)
				$(LIB) $(NAME) $(OBJS)
				ranlib $(NAME)

$(BUILD_DIR)/%.o:  $(SRC_DIR)/%.c
				@if [ ! -d $(dir $@) ] ; then $(MKDIR) $(dir $@); fi
				$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
				$(RM) $(OBJS)
				$(RM) $(DEPS)

fclean:			clean
				$(RM) $(NAME)

re:
				$(MAKE) fclean
				$(MAKE) all

ifeq ($(findstring $(MAKECMDGOALS), clean fclean re),)
	-include $(DEPS)
endif
.PHONY:			all, clean, fclean, re
