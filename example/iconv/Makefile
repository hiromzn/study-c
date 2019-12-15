
CC = gcc

CFLAGS = -g -Wall -std=c99
# MAC # CFLAGS = -g -Wall -std=c99 -liconv

srcs = $(wildcard *.c)

tgt = $(srcs:.c=)

all : $(tgt)

$(tgt): %: %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) *~

run :
	./runtest $(tgt)
