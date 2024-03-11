CC = cc
CFLAGS = -Wall -Wextra -Werror -g
TSRCS = $(wildcard t/*.c)
TESTS = $(TSRCS:.c=.t)

all: $(TESTS)

$(TESTS): %.t: %.o get_next_line.o tap.o
	$(CC) $(CFLAGS) -o $@ $^

tap.o: tap.c tap.h

get_next_line.o: get_next_line.c get_next_line.h

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

run: all
	prove

clean:
	rm -f *.o t/*.o

fclean: clean
	rm -f $(TESTS)

re: fclean all
