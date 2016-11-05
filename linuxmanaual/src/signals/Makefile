#
t_sigaltstack:t_sigaltstack.o ../lib/get_num.o ../lib/error_functions.o
	cc -o t_sigaltsttack t_sigaltstack.o ../lib/get_num.o ../lib/error_functions.o
t_sigaltstack.o:t_sigaltstack.c ../lib/tlpi_hdr.h
	cc -o t_sigaltstack.o -c t_sigaltstack.c
../lib/get_num.o:../lib/get_num.c ../lib/tlpi_hdr.h
	cc -c  ../lib/get_num.c -o ../lib/get_num.o
../lib/error_functions.o:../lib/error_functions.c ../lib/error_functions.h ../lib/ename.c.inc ../lib/tlpi_hdr.h
	cc -o ../lib/error_functions.o -c ../lib/error_functions.c