
CC = gcc

CFLAGS = -g -Wall
# MAC # CFLAGS = -g -Wall -std=c99 -liconv

srcs = $(wildcard *.c)

tgt = $(srcs:.c=)

all : $(tgt)

$(tgt): %: %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) *~
	rm -rf $(tgt).dSYM

run :
	./runtest $(tgt)
