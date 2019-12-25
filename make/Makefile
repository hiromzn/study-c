#
# SILENT demo
#
#   default : silent mode
#   usage of no silent : make SILENT_FLAG="" all
#
SILENT_FLAG = .SILENT

$(SILENT_FLAG) :

CC = gcc

CFLAGS = -g -Wall -std=c99

srcs = $(wildcard *.c)

tgt = $(srcs:.c=)

all : $(tgt)

$(tgt): %: %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) *~


