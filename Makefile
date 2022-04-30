CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC = src
OBJ = obj
BIN = bin

SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
CURRENTDIR = $(notdir $(shell pwd))

all: $(OBJECTS) $(BIN)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN)/$(CURRENTDIR).out

$(BIN):
	mkdir -p bin

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)
	$(CXX) -I$(SRC) -c $< -o $@

$(OBJ):
	mkdir -p obj

clean:
	rm -f obj/*.o bin/*.out
