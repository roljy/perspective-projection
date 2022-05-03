CXX = g++
CXXFLAGS = -Wall -std=c++17
DBFLAGS = -O1 -g

SRC = src
OBJ = obj
BIN = bin

SOURCES = $(wildcard $(SRC)/*.cpp)
PROBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/pr_%.o, $(SOURCES))
DBOBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/db_%.o, $(SOURCES))
CURRENTDIR = $(notdir $(shell pwd))

all: $(PROBJECTS) $(BIN)
	$(CXX) $(CXXFLAGS) $(PROBJECTS) -o $(BIN)/$(CURRENTDIR).out

debug: $(DBOBJECTS) $(BIN)
	$(CXX) $(CXXFLAGS) $(DBFLAGS) $(DBOBJECTS) -o $(BIN)/db_$(CURRENTDIR).out

$(BIN):
	mkdir -p bin

$(OBJ)/pr_%.o: $(SRC)/%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -I$(SRC) -c $< -o $@

$(OBJ)/db_%.o: $(SRC)/%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) $(DBFLAGS) -I$(SRC) -c $< -o $@

$(OBJ):
	mkdir -p obj

clean:
	rm -f obj/*.o bin/*.out
