
CC = gcc

CFLAGS = -g -Wall -std=c99

srcs = $(wildcard *.c)

tgt = $(srcs:.c=)

all : $(tgt)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) *~
	rm -fr $(tgt).dSYM

