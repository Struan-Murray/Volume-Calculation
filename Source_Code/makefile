CC:=g++
CXXREQUIREMENTS:= -std=c++17
CXXFLAGSDEBUG:= -Og -g
CXXFLAGSFULL:= -O3  -s
CXXWARNINGS:= -Wall -Weffc++ -Wextra -Wpedantic
INPUT:= main.cpp
TITLE:= 'Vat Volume Calculations'
FILES:= #files_setup.hpp confirm.cpp main.cpp ShapeVolume.hpp

debug: $(INPUT) $(FILES)
	$(CC) $(INPUT) $(FILES) -o debug $(CXXREQUIREMENTS) $(CXXFLAGSDEBUG) $(CXXWARNINGS)

full: $(INPUT) $(FILES)
	$(CC) $(INPUT) $(FILES) -o full $(CXXREQUIREMENTS) $(CXXFLAGSFULL)
	mv full $(TITLE)

all: full debug

clean:
	rm full debug vats/*.csv $(TITLE) || true
	rm -r vats logs
