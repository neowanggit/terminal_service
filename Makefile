#


CC=gcc
CFLAGS+=-c -Wall -D_REENTRANT 

LIBS= -lc -lulfius -lorcania -ljansson

LIBS+= -lyder

all: terminal_service

clean:
	rm -f *.o terminal_service

debug: ADDITIONALFLAGS=-DDEBUG -g -O0

debug: terminal_service


%.o: %.c
	$(CC) $(CFLAGS) $<  -DDEBUG -g -O0

terminal_service: terminal_service.o terminals.o
	$(CC) -o terminal_service terminal_service.o terminals.o $(LIBS)
