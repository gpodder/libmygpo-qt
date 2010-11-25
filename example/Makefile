CC=g++
CFLAGS=-c -g -Wall $(shell pkg-config QtGui QtCore QtNetwork libmygpo-qt --cflags)
LIBS= $(shell pkg-config QtGui QtCore QtNetwork libmygpo-qt --libs)
SRCDIR=src

all: main

main: $(SRCDIR)/main.o 
	$(CC) $(SRCDIR)/main.o -o main $(LIBS)

$(SRCDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o


make clean:
	rm -fr $(SRCDIR)/*.moc $(SRCDIR)/*.o main
