
CC = gcc

CFLAGS = -g -Wall -std=c99
CF32 = -m32
CF64 = -m64

srcs = $(wildcard *.c)

exe32 = $(srcs:.c=.32)
exe64 = $(srcs:.c=.64)

tgt = $(exe32) $(exe64)

all : $(tgt)

%.32: %.c
	$(CC) $(CF32) $(CFLAGS) $< -o $@
%.64: %.c
	$(CC) $(CF64) $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) *~
	rm -fr $(tgt).dSYM

