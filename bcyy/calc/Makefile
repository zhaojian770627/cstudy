#
#GPATH=
#VPATH=
CFLAGS+=-g
OBJECTS=
EXEF:=mycalc lexicalanalyzer parser
all:$(EXEF)
parser:parser.o gettoken.o
lexicalanalyzer:lexicalanalyzer.o
#gettoken.o:gettoken.c
mycalc:y.tab.c lex.yy.c
	cc -o mycalc y.tab.c lex.yy.c
y.tab.c:
	yacc -dv mycalc.y
lex.yy.c:
	lex mycalc.lex
clean:
	$(RM) *.o *.d y.tab.h y.tab.c lex.yy.c  *.output  $(EXEF)