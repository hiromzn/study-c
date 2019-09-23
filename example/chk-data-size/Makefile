
all : chk32 chk64

chk32 :
	make COPT=-m32 EXE=chk32 exe

chk64 :
	make COPT=-m64 EXE=chk64 exe

exe : chkdatasize.c
	cc -o $(EXE) -g $(COPT) chkdatasize.c

