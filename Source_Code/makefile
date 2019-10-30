CC:=g++
CXXFLAGSR:= -O3  -s
CXXFLAGSD:= -g
CXXW:= -Wall -Weffc++ -Wextra -Wpedantic

main: main.cpp
	$(CC) main.cpp -o main $(CXXW) $(CXXFLAGSR) 

debug: main.cpp
	$(CC) main.cpp -o debug $(CXXW) $(CXXFLAGSD)

all: main debug

clean:
	rm main debug *.csv
