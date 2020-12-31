
TGT = connect_timeout.o
TEST = main

test : $(TEST) ftest

all : $(TGT)

$(TEST) : $(TGT) $(TEST:=.c)
	gcc -g -o main main.c $(TGT)

$(TGT) : $(TGT:.o=.c)
	gcc -g -c $?

clean :
	rm -rf $(TGT) $(TEST) $(TGT:.o=) *.dSYM

ftest :
	gcc -g -o $(TGT:.o=) connect_timeout.c -DTEST_MAKE
