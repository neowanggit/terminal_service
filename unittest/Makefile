#


CC=gcc
CFLAGS+=-c -Wall -D_REENTRANT -I ../

LIBS= -lc -lulfius -lorcania -ljansson

LIBS+= -lyder -lcunit

all: terminal_ut

clean:
	rm -f *.o terminal_ut

%.o: %.c
	$(CC) $(CFLAGS) $<  -o $@ -DDEBUG -g -O0

terminal_ut: terminal_ut.o ../terminals.o
	$(CC) -o terminal_ut terminal_ut.o  ../terminals.o $(LIBS)
