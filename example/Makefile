CC=g++
CFLAGS=-c -g -Wall $(shell pkg-config libmygpo-qt --cflags)
LIBS= $(shell pkg-config libmygpo-qt --libs)
SRCDIR=src

all: main

main: $(SRCDIR)/main.o 
	$(CC) $(SRCDIR)/main.o -o main $(LIBS)

qt5:
	$(CC) -c -I/home/horrendus/kde/include/mygpo-qt -I/usr/include/qt5/QtCore -I/usr/include/qt5 -I/usr/include/qt5/QtNetwork -fPIC $(SRCDIR)/main.cpp -o $(SRCDIR)/main_qt5.o
	$(CC) $(SRCDIR)/main_qt5.o -o main -L/home/horrendus/kde/lib -lmygpo-qt -lQt5Network -lQt5Core

$(SRCDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/main.cpp -o $(SRCDIR)/main.o


make clean:
	rm -fr $(SRCDIR)/*.moc $(SRCDIR)/*.o main
