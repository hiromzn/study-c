
CLANG = clang

AST_FLAGS = -cc1 -ast-dump

astall = test.h.ast

all : $(astall)

h.ast : .h
	clang -cc1 -ast-dump $< >$*


headers = $(wildcard test*.h)

tgt = $(headers:.h=.h.ast)

all : $(tgt)

%.h.ast: %.h
	$(CLANG) $(AST_FLAGS) $< >$@

clean :
	rm -f $(tgt)
