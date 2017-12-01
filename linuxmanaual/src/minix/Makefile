#
GPATH=../lib 
VPATH=../lib 
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=testsize installboot
all:$(EXEF)
testsize:testsize.o
installboot:installboot.o

clean:
	$(RM) *.o *.d $(EXEF)