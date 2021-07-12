CC=g++
CFLAGS=-Wall -Werror -g -std=c++20
LDFLAGS=
TARGET=tensor view


all:	tensor view

tensor: main.h
	$(CC) tensor.cpp -o tensor $(CFLAGS)

view: 	main.h
	$(CC) view.cpp -o view $(CFLAGS)

test:	all
	./tensor && ./view
clean:	

mrproper: clean
	rm $(TARGET)
