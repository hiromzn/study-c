ORACLE_HOME	= /opt/extract/oracle/product/12.1.0/dbhome_1
PROC	= $(ORACLE_HOME)/bin/proc
PROCFLAGS	= -I$(ORACLE_HOME)/precomp/public

LDPATH	= LD_LIBRARY_PATH=$(ORACLE_HOME)/lib

TARGET  = ./hello
SRCDIR  = .
PCSRC   = \
	$(SRCDIR)/hello.pc \

CCINC = \
	-I$(ORACLE_HOME)/precomp/public \
	-I$(ORACLE_HOME)/rdbms/public \
	-I$(ORACLE_HOME)/plsql/public \
	-I$(ORACLE_HOME)/network/public \

CPPOBJS = $(PCSRC:.pc=.c)

OBJECTS = $(CSRCS:.c=.o) \
	  $(CXXSRC:.cpp=.o) \
	  $(CPPOBJS:.c=.o)

CCLIB   = \
	-L$(PHOME)/lib \
	-L$(ORACLE_HOME)/lib \
	-L$(ORACLE_HOME)/precomp/lib

LDLIB   = \
	-lclntsh \
	-lclntshcore \
	-lmql1 \
	-lipc1 \
	-lnnz12 \
	-lons \
	`cat $(ORACLE_HOME)/lib/sysliblist`


all : $(TARGET)

run :
	$(LDPATH) $(TARGET)

$(TARGET) : $(OBJECTS) $(ARCS)
	$(CC) $(CFLAGS) $(CCLIB) $(LDLIB) -o $@ $(OBJECTS) $(ARCS)

.c.o : 
	$(CC) $(CFLAGS) $(CCINC) -c $< -o $@

.cpp.o : 
	$(CXX) $(CFLAGS) $(CCINC) -c $< -o $@

cproto :
	@cproto $(CCINC) $(PCSRC:.pc=.c) $(CSRCS)

$(CPPOBJS) :
	$(LDPATH) $(PROC) $(PROCFLAGS)  iname=$(@:.c=.pc) oname=$@

clean :
	rm -f $(OBJECTS) $(TARGET) $(CPPOBJS) $(PCSRC:.pc=.lis) core 
