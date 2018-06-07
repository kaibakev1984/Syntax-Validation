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
run1: all clear
	./$(EXEC)
run: all clear
	# Caso archivo vacío
	cat script_vacio.txt | ./$(EXEC)
	# Casos particulares
	cat script2.txt | ./$(EXEC)
	# Casos borde proporcionados por la cátedra
	cat script.txt | ./$(EXEC)
clear:
	clear
valgrind: all clear
	valgrind $(VFLAGS) ./$(EXEC) < script_vacio.txt
	valgrind $(VFLAGS) ./$(EXEC) < script.txt
	valgrind $(VFLAGS) ./$(EXEC) < script2.txt
gdb: all clear
	gdb -tui ./$(EXEC)
