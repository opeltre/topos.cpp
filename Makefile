CC=g++
CFLAGS=-Wall -Werror -g -std=c++20
LDFLAGS=
TARGET=tensor view


all:	tensor view

tensor: topos.h
	$(CC) tensor.cpp -o tensor $(CFLAGS)

view: 	topos.h
	$(CC) view.cpp -o view $(CFLAGS)

test:	all
	./tensor && ./view
clean:	

mrproper: clean
	rm $(TARGET)
