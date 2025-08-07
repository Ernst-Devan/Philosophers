NAME := philo

# --- SRC/DIR --- #

SRC_DIR := src/

SRCS = philosophers.c \
	   check.c		  \
	   init.c		  \
	   utils.c		  \
	   fork.c		  \
	   time.c		  \
	   thread.c		  \
	   routine.c	  \
	   start.c		  \
	   print.c		  \
	   death.c	      \

# --- INCLUDES --- #

INCLUDES := includes/

# --- OBJS/DEPS --- #

OBJS_DIR := .build/objs/

OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))


DEPS := $(OBJS:.o=.d)

# --- FLAGS --- #

CPPFLAGS += -MMD -MP $(addprefix -I,$(INCLUDES))

CFLAGS += -g3 -Wall -Wextra -Werror -lpthread

# --- COMPILATER --- #

CC = gcc

# --- EXEC --- #

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $^ -o $@

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

force:

.PHONY : clean fclean all re print-% debug force

clean:
	rm -rf .build

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind_readline.supp ./$(NAME)

print-%:
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

-include $(DEPS)
