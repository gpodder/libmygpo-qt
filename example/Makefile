CC=g++
CFLAGS=-c -g -Wall -I$(HOME)/kde/include/mygpo-qt/ $(shell pkg-config QtCore QtWebKit --cflags)
LIBS=-L$(HOME)/kde/lib/ -l$(HOME)/kde/lib/libmygpo-qt.so $(shell pkg-config QtCore QtWebKit --libs)
SRCDIR=src

all: main

main: main.o 
	$(CC) $(SRCDIR)/main.o -o main $(LIBS)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o


make clean:
	@rm -fr $(BUILDDIR)/* $(SRCDIR)/*.moc
