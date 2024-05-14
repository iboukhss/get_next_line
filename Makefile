NAME = libgnl.a
CC = clang
CFLAGS = -Wall -Wextra -g -MMD -fsanitize=undefined
LDFLAGS = -L.
LDLIBS = -ltap -lgnl -lbsd

# Main sources
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
INCS = get_next_line.h

# Bonus sources
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_INCS = get_next_line_bonus.h

# Test sources
TEST_SRCS = t/get_next_line.c
TEST_EXES = $(TEST_SRCS:.c=.t)

all: $(NAME)

libgnl.a: $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

tests: $(TEST_EXES)

%.t: %.c libtap.a libgnl.a
	$(CC) $(CFLAGS) -I. -o $@ $< $(LDFLAGS) $(LDLIBS)

libtap.a: t/tap.c
	$(CC) $(CFLAGS) -c -o t/tap.o $<
	ar rcs $@ t/tap.o

norm:
	-norminette $(SRCS) $(INCS) $(BONUS_SRCS) $(BONUS_INCS)

clean:
	rm -f *.o t/*.o
	rm -f *.d t/*.d

fclean: clean
	rm -f *.a
	rm -f t/*.t

re: fclean all

-include $(DEPS)

.PHONY: all norm tests clean fclean re
