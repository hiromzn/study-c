
GCC	= gcc

GCCOPT	= -m64 -Wall $(GCCWOPT) $(GCCPROTOOPT)
GCCWOPT = -Wundef -Wempty-body -Wfloat-equal -Wextra -Wno-unused-parameter -Wno-missing-field-initializers
#ALL# GCCWOPT = -Wundef -Wempty-body -Wfloat-equal -Wextra
GCCPROTOOPT = -Wmissing-prototypes -Wstrict-prototypes

SRCDIR	= ./

SRCS	= test.c

EXES	= $(SRCS:.c=)

all : $(EXES)

test : test.c
	$(CC) $(GCCWOPT) -o $@ $<

clean :
	rm -f $(EXES)

