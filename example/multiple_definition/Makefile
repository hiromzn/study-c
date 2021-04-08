
CC = gcc

# DEFS = -DMULTI_DEF
CFLAGS = -g -Wall -std=c99 $(DEFS)

srcs = $(wildcard *.c)
objs = $(srcs:.c=.o)

tgt = main

all : $(tgt)

$(tgt) : $(objs)
	$(CC) $(CFLAGS) $^ -o $@

%.c: %.o
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) $(objs) *~
	rm -fr $(tgt).dSYM

