CC=g++
CFLAGS=-Wall -Werror -g -std=c++20
INCLUDE=-I$(PWD)/
LDFLAGS=
TEST=$(wildcard test/*.cpp)
TARGET=$(TEST:.cpp=.out)

all:	$(TARGET)

%.out: 	%.cpp
	$(CC) $< -o $@ $(CFLAGS) $(INCLUDE) 

%.run:	%.out
	echo '' && ./$< && echo '------' && echo ''

test:	all

test.run: $(TARGET:.out=.run)
	
clean:	
	rm test/*.out
