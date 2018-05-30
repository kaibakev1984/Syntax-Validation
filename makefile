CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --show-reachable=yes --track-origins=yes
EXEC = pruebas
OBJFILES = syntax_val.o pila.o 

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(EXEC)
all: clear $(EXEC)

free: *.o
	rm -f *.o pruebas

run: all clear
	./$(EXEC)
clear:
	clear
valgrind: all clear
	valgrind $(VFLAGS) ./$(EXEC)
gdb: all clear
	gdb -tui ./$(EXEC)
