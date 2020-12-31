
TGT = connect_timeout.o
TEST = main

all : $(TGT)

test : $(TEST)

$(TEST) : $(TGT) $(TEST:=.c)
	gcc -g -o main main.c $(TGT)

$(TGT) : $(TGT:.o=.c)
	gcc -g -c $?

clean :
	rm -rf $(TGT) $(TEST)
