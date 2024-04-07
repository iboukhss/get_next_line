CC = clang
CFLAGS = -Wall -Wextra -g
LDFLAGS = -L.
LDLIBS = -ltap -lgnl -lbsd

SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
TEST_SRCS = $(wildcard t/*.c)
TEST_EXES = $(TEST_SRCS:.c=.t)

ifdef BUFSIZ
	CFLAGS += -DBUFFER_SIZE=$(BUFSIZ)
endif

ifdef DBG
	CFLAGS += -DDEBUG
endif

all: $(TEST_EXES)

libtap.a: tap.o
	ar rcs $@ $<

tap.o: tap.c tap.h
	$(CC) $(CFLAGS) -c -o $@ $<

libgnl.a: $(OBJS)
	ar rcs $@ $^

%.o: %.c get_next_line.h debug.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.t: %.c libtap.a libgnl.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

norm:
	-norminette $(SRCS) get_next_line.h

clean:
	rm -f *.o

fclean: clean
	rm -f *.a
	rm -f t/*.t

re: fclean all

.PHONY: all norm clean fclean re
