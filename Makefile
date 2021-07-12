CC=g++
CFLAGS=-Wall -Werror -g -std=c++20
INCLUDE=-I$(PWD)/
LDFLAGS=
TEST=$(wildcard test/*.cpp)
TARGET=$(TEST:.cpp=.out)

all:	$(TARGET)

%.out: 	%.cpp
	$(CC) $< -o $@ $(CFLAGS) $(INCLUDE)

test:	all
	./test/run.sh
clean:	

mrproper: clean
	rm $(TARGET)
