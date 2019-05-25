test_flag_storing: *.c
	gcc -g -O2 -o $@ $<
all: test_flag_storing 
