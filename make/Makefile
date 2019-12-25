
SILENT_FLAG = .SILENT

CC = gcc

CFLAGS = -g -Wall -std=c99

srcs = $(wildcard *.c)

tgt = $(srcs:.c=)

all : $(tgt)

$(tgt): %: %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) *~

$(SILENT_FLAG) :

#.SILENT : $(SILENT_FLAG)
