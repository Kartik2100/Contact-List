CC = gcc
CFLAGS = -ansi -Wall -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

SOURCES = $(SRCDIR)*.c

all: contactList

contactList: $(BINDIR)mainA4.o $(BINDIR)function.o
	$(CC) $(BINDIR)mainA4.o $(BINDIR)function.o -o $(BINDIR)contactList

$(BINDIR)mainA4.o: $(SRCDIR)mainA4.c
	$(CC) $(CFLAGS) -c $(SRCDIR)mainA4.c -o $@

$(BINDIR)function.o: $(SRCDIR)function.c
	$(CC) $(CFLAGS) -c $(SRCDIR)function.c -o $@

run:
	($BINDIR)contactList

clean:
	rm ./bin/*.o ($BINDIR)contactList
