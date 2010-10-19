CC=g++
CFLAGS=-c -g -Wall $(shell pkg-config QtCore QtWebKit --cflags)
LIBS=$(shell pkg-config QtCore QtWebKit --libs)
SRCDIR=src
BUILDDIR=build

all: main

main: main.o Example.o moc_Example.o
	$(CC) $(BUILDDIR)/main.o $(BUILDDIR)/Example.o $(BUILDDIR)/moc_Example.o -o $(BUILDDIR)/main $(LIBS)

main.o: src/main.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/main.cpp -o $(BUILDDIR)/main.o

Example.o: src/Example.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/Example.cpp -o $(BUILDDIR)/Example.o

moc_Example.o: moc_Example.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/moc_Example.cpp -o $(BUILDDIR)/moc_Example.o

moc_Example.cpp: src/Example.cpp
	moc-qt4 $(SRCDIR)/Example.h -o $(SRCDIR)/moc_Example.cpp

make clean:
	@rm -fr $(BUILDDIR)/* $(SRCDIR)/moc_Example.cpp