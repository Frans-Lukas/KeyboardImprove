CC=gcc
CFLAGS=-std=gnu11 -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes \
	-Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused \
	-Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default \
	-Wunreachable-code -g
TARGET=keyImprove

all: 		clean keyImprove 

keyImprove:		execute.o keyboardImprove.o 
	@ $(CC) $(CFLAGS) -o $(TARGET) execute.o keyboardImprove.o 

keyboardImprove.o: 		keyboardImprove.c
	@ $(CC) $(CFLAGS) -c keyboardImprove.c 

execute.o:		execute.c execute.h
	@ $(CC) $(CFLAGS) -c execute.c

clean: 
	@ rm -f keyboardImprove  *.o core
