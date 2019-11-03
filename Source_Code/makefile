CC:=g++
CXXFLAGSR:= -O3  -s
CXXFLAGSD:= -g
CXXW:= -Wall -Weffc++ -Wextra -Wpedantic
FILES:= main.cpp ShapeVolume.hpp Confirm.hpp

debug: $(FILES)
	$(CC) main.cpp -o debug $(CXXW) $(CXXFLAGSD)

main:: $(FILES)
	$(CC) main.cpp -o main $(CXXFLAGSR) 

all: main debug

clean:
	rm main debug *.csv
