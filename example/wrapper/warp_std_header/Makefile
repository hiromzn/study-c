
GCC	= gcc
GCCOPT	= -Wall $(GCCWOPT) $(GCCPROTOOPT)
GCCWOPT = -Wundef -Wempty-body -Wfloat-equal -Wextra -Wno-unused-parameter -Wno-missing-field-initializers
#ALL# GCCWOPT = -Wundef -Wempty-body -Wfloat-equal -Wextra
GCCPROTOOPT = -Wmissing-prototypes -Wstrict-prototypes

SRCDIR	= ./
GETSRCS	= `echo $(SRCDIR)/*.c`
SRCS	= $(GETSRCS)

EXES	= $(SRCS:.c=)

all : gcc

gcc :
	make -i SRCS="$(SRCS)" CC=$(GCC) COPT="$(GCCOPT) $(GCCPROTOOPT) $(COPT)" exes

exes : $(EXES)

.c. :
	@ echo "##### compile: $<"
	@ echo "##### command: $(CC) $(COPT) -c -o $@ $<"
	-@ $(CC) $(COPT) -c -o $@ $<

clean :
	make SRCS="$(SRCS)" clean_exes

clean_exes :
	rm -f $(EXES)

