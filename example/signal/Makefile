#

SILENT_FLAG = .SILENT
#$(SILENT_FLAG) :

# source directory
SRC = .

CC = gcc

#CFLAGS = -g -Wall

srcs = $(wildcard $(SRC)/*.c)

tgt = $(srcs:.c=)

all : $(tgt)

.c. :
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f $(tgt) *~ 
	rm -rf $(SRC)/*.dSYM

