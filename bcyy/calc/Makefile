#
#GPATH=../lib ../time ../svsem 
#VPATH=../lib ../time ../svsem
CFLAGS+=-g
OBJECTS=
EXEF:=mycalc
all:$(EXEF)
mycalc:y.tab.c lex.yy.c
	cc -o mycalc y.tab.c lex.yy.c
y.tab.c:
	yacc -dv mycalc.y
lex.yy.c:
	lex mycalc.lex
clean:
	$(RM) *.o *.d *.h *.c *.output  $(EXEF)